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
    priority = 1;
    outAccel = 0;
}

//AxisRacer::~AxisRacer()
//{
//}


void AxisRacer::first()
{
    // start at idle
    setState(eSTATE_IDLE);
    
    // connect to specific joints
    connectOutput();
    // tune PID controller
    oPIDControl.init(4.0, 0.0, 2.0);

    log4cxx::NDC::push(modName);   	
}
                    

// drives the axis towards the target position
void AxisRacer::loop()
{
    senseBus();

    int state = getState();
    // skip if DONE or BLOCKED
    if (state == eSTATE_IDLE ||state == eSTATE_BLOCKED)            
        return;
            
    switch (state)
    {
        case eSTATE_GO:     

            //reset controller
            oPIDControl.reset();
            setState(eSTATE_DRIVE);
            break;  

        case eSTATE_DRIVE:
            // drive joint

            // if movement blocked -> BLOCKED
            if (checkBlocked())
                setState(eSTATE_BLOCKED);   
            // otherwise, move arm
            else
            {
                // PID control 
                outAccel = oPIDControl.control(targetSpeed - istSpeed);              
                writeBus();
                LOG4CXX_INFO(logger, "outAccel = " << outAccel << ", istSpeed = " << istSpeed);                
            }
            break;
    }   // end switch    

    if (isStateChanged())
        showState();

    writeBus();        
}


bool AxisRacer::checkBlocked()
{
    int moveSign = (targetSpeed > 0.0 ? 1: -1);

    // check if movement is blocked (pushing beyond the joint's limit)    
    return ((jointLimit > 0 && moveSign > 0) || (jointLimit < 0 && moveSign < 0));
}


void AxisRacer::showState()
{
    switch (getState())
    {
        case eSTATE_IDLE:
            LOG4CXX_INFO(logger, ">> idle");
            break;
                        
        case eSTATE_GO:
            LOG4CXX_INFO(logger, ">> go");
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