/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/AxisRacer.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AxisRacer::logger(Logger::getLogger("amy.arm"));

AxisRacer::AxisRacer()
{
    modName = "AxisRacer";
    // control priority
    priority = oArmConfig.getPriority4AxisRacers();
}

void AxisRacer::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}

void AxisRacer::first()
{
    // start at done
    setState(eSTATE_DONE);
    // connect to controlled joint (defined in derived modules)
    setSpecificConnections();    
    // tune PID controller
    float* pPID = oArmConfig.getPIDRacer();
    oPIDControl.init(pPID[0], pPID[1], pPID[2]);
    speed1 = speed2 = 0.0;
    silentCycles = 0;

    log4cxx::NDC::push(modName);   	
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

        // update target speed 
        updateTargetSpeed();
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


void AxisRacer::updateTargetSpeed()
{
    targetSpeed = speed1 + speed2;  
}

bool AxisRacer::checkBlocked()
{
    // check if movement is blocked (pushing beyond the joint's limit)
    if (jointLimit != 0 && targetSpeed != 0.0)
        return ((targetSpeed > 0.0 && jointLimit > 0) || (targetSpeed < 0.0 && jointLimit < 0));
    else
        return false;
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