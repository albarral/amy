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
    setControlledJoint();    
    // tune PID controller
    float* pPID = oArmConfig.getPIDRacer();
    oPIDControl.init(pPID[0], pPID[1], pPID[2]);
    speed1 = speed2 = 0.0;

    log4cxx::NDC::push(modName);   	
}
                    

// drives the axis towards the target position
void AxisRacer::loop()
{
    senseBus();

    int state = getState();
    // skip if DONE or BLOCKED
    if (state == eSTATE_DONE ||state == eSTATE_BLOCKED)            
        return;
            
    switch (state)
    {
        case eSTATE_NEWMOVE:     

            //reset PID controller
            oPIDControl.reset();
            outAccel = 0.0;
            targetSpeed = speed1 + speed2;
            if (targetSpeed != 0.0)
                setState(eSTATE_DRIVE);
            // zero speed requested -> DONE
            else
                setState(eSTATE_DONE);                            
            // show data
            LOG4CXX_INFO(logger, ">> new request");  
            LOG4CXX_INFO(logger, "target speed = " << targetSpeed);  
            break;  

        case eSTATE_DRIVE:
            // drive arm

            // compute movement acceleration
            outAccel = oPIDControl.control(targetSpeed - axisSpeed);                      
            // if movement blocked -> BLOCKED
            if (checkBlocked())
                    setState(eSTATE_BLOCKED);   
            
            LOG4CXX_INFO(logger, " sollSpeed=" + std::to_string(targetSpeed) + " istSpeed=" + std::to_string(axisSpeed) +  ", accel=" + std::to_string(outAccel) + "]");
            break;
    }   // end switch    

    if (isStateChanged())
        showState();

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


void AxisRacer::showState()
{
    switch (getState())
    {
        case eSTATE_DONE:
            LOG4CXX_INFO(logger, ">> done");
            break;
                        
        case eSTATE_NEWMOVE:
            LOG4CXX_INFO(logger, ">> new move");
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