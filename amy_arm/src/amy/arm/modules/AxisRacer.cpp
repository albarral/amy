/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/AxisRacer.h"
#include "amy/core/robot/Arm.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AxisRacer::logger(Logger::getLogger("amy.arm"));

AxisRacer::AxisRacer()
{
    modName = "AxisRacer";
    targetAxis = -1;
    pAxisBus = 0;
    pJointBus = 0;
    // control priority
    priority = oArmConfig.getPriority4AxisRacers();
}

void AxisRacer::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}

bool AxisRacer::setTargetAxis(int value)
{
    // safety check
    if (Arm::isValidAxis(value))
    {
        targetAxis = value;
        bool bok = true;    
        switch (targetAxis)
        {
            case Arm::eAXIS_PAN:
                modName = "PanRacer";
                break;
            case Arm::eAXIS_TILT:
                modName = "TiltRacer";
                break;
            case Arm::eAXIS_RADIAL:
                modName = "RadialRacer";
                break;                        
            default:
                bok = false;
        }
        return bok;
    }
    else    
        return false;        
}

void AxisRacer::first()
{
    // connect to proper joint, end if failed
    if (!setConnections())    
    {
        LOG4CXX_WARN(logger, modName << " couldn't connect to proper axis. Ending module!");
        tron::Module3::off();
        return;
    }

    // start at done
    setState(eSTATE_DONE);
    // tune PID controller
    float* pPID = oArmConfig.getPIDRacer();
    oPIDControl.init(pPID[0], pPID[1], pPID[2]);
    targetSpeed = 0.0;
    silentCycles = 0;

    log4cxx::NDC::push(modName);   	
}
                    
bool AxisRacer::setConnections()
{
    // safety check
    if (pArmBus == 0)
        return false;

    bool bok = true;    
    switch (targetAxis)
    {
        case Arm::eAXIS_PAN:
            pAxisBus = &(pArmBus->getPanBus());
            // control HS joint 
            pJointBus = &(pArmBus->getBusHS());
            break;
        case Arm::eAXIS_TILT:
            pAxisBus = &(pArmBus->getTiltBus());
            // control VS joint 
            pJointBus = &(pArmBus->getBusVS());
            break;
        case Arm::eAXIS_RADIAL:
            pAxisBus = &(pArmBus->getRadialBus());
            // control ELB joint
            pJointBus = &(pArmBus->getBusEL());
            break;                        
        default:
            bok = false;
    }
    
    return bok;
}

// drives the axis towards the target position
void AxisRacer::loop()
{
    senseBus();

    // if control requested
    if (brequested)
    {    
        silentCycles = 0;

        // exit from DONE 
        if (getState() == eSTATE_DONE)            
            setState(eSTATE_NEWMOVE);                           
    }
    else
        silentCycles++;
    
    if (getStable() == 0)
        showState();
    
    switch (getState())
    {
        case eSTATE_DONE:
            // skip if DONE
            return;
            
        case eSTATE_NEWMOVE:     

            // if movement blocked -> BLOCKED
            if (checkBlocked())
            {
                outAccel = 0;                    
                setState(eSTATE_BLOCKED);   
            }
            // otherwise -> DRIVE
            else
            {
                //reset PID controller
                oPIDControl.reset();
                outAccel = 0.0;            
                setState(eSTATE_DRIVE);
            }
            break;  

        case eSTATE_DRIVE:
            // drive arm

            // if movement blocked -> BLOCKED
            if (checkBlocked())
            {
                outAccel = 0;                    
                setState(eSTATE_BLOCKED);
            }
            // if null speed requested & confirmed -> DONE
            else if (silentCycles > 3 && targetSpeed == 0)
            {
                outAccel = 0;                    
                setState(eSTATE_DONE);   
            }
            else
                // compute movement acceleration
                outAccel = oPIDControl.control(targetSpeed - axisSpeed);                      
            
            LOG4CXX_DEBUG(logger, " sollSpeed=" + std::to_string(targetSpeed) + " istSpeed=" + std::to_string(axisSpeed) +  ", accel=" + std::to_string(outAccel) + "]");
            break;

        case eSTATE_BLOCKED:
            // blocked arm

            if (checkBlocked())                    
                outAccel = 0;                    
            // if movement not blocked anymore -> NEWMOVE
            else
                setState(eSTATE_NEWMOVE);   
            break;
    }   // end switch    

    writeBus();        
}

bool AxisRacer::checkBlocked()
{
    // check if movement is blocked (pushing beyond the joint's limit)
    if (jointLimit != 0 && targetSpeed != 0.0)
        return ((targetSpeed > 0.0 && jointLimit > 0) || (targetSpeed < 0.0 && jointLimit < 0));
    else
        return false;
}

void AxisRacer::senseBus()
{
    // sense axis speeds adder -> NEWMOVE
    if (pAxisBus->getCO_AXIS_SPEEDS().checkRequested())
    {
        targetSpeed = pAxisBus->getCO_AXIS_SPEEDS().getValue();
        brequested = true;
    }
    else
        brequested = false;
    
    // sense axis speed
    axisSpeed= pAxisBus->getSO_AXIS_SPEED().getValue();    
    // sense reached joint limit
    jointLimit = pJointBus->getSO_JOINT_LIMIT_REACHED().getValue();
}

void AxisRacer::writeBus()
{  
    // control joint
    pJointBus->getCO_JOINT_ACCEL().request(outAccel, priority);
}


void AxisRacer::showState()
{
    switch (getState())
    {
        case eSTATE_DONE:
            LOG4CXX_INFO(logger, ">> done");
            break;
                        
        case eSTATE_NEWMOVE:
            LOG4CXX_INFO(logger, ">> new move - speed = " << targetSpeed);
            break;

        case eSTATE_DRIVE:
            LOG4CXX_INFO(logger, ">> drive");
            break;

        case eSTATE_BLOCKED:
            LOG4CXX_INFO(logger, ">> blocked");
            break;
    }   // end switch    
}

}