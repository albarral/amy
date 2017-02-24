/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/TiltKeeper.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr TiltKeeper::logger(Logger::getLogger("amy.arm"));

TiltKeeper::TiltKeeper()
{
    modName = "TiltKeeper";
    priority = 1;
    pVSBus = 0;
    pELBus = 0;
}
 
void TiltKeeper::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}

void TiltKeeper::first()
{
    setState(eSTATE_DONE);
    // connect to specific joints
    pVSBus = &pArmBus->getBusVS();
    pELBus = &pArmBus->getBusEL();
    // tune PID controller
    float* pPID = oArmConfig.getPIDTiltKeeper();
    oPIDControl.init(pPID[0], pPID[1], pPID[2]);
    
    log4cxx::NDC::push(modName);   	
}
                    

// computes the axes positions
void TiltKeeper::loop()
{    
    senseBus();

    // if DONE, skip
    if (getState() == eSTATE_DONE)
        return;

    // activated module
    switch (getState())
    {        
        case eSTATE_WATCH:     

            // if elbow changing -> DRIVE
            if (elbowSpeed != 0.0)
            {
                //reset controller
                oPIDControl.reset();
                setState(eSTATE_DRIVE);
            }
            break;  

        case eSTATE_DRIVE:

            // if elbow stable -> WATCH
            if (elbowSpeed == 0.0)
                setState(eSTATE_WATCH);                
            // otherwise, move VS
            else
            {
                // PID control with error = 0 - tiltSpeed
                outAccel = oPIDControl.control(-tiltSpeed);              
                writeBus();
                LOG4CXX_INFO(logger, "outAccel = " << outAccel << ", tiltSpeed = " << tiltSpeed);                
            }
            break;              
    }
    
    if (isStateChanged())
        showState();
}


void TiltKeeper::senseBus()
{
    if (pArmBus->getCO_KEEP_TILT().checkRequested())
    {
        // if activated -> WATCH
        if (pArmBus->getCO_KEEP_TILT().getValue() == true)    
            setState(eSTATE_WATCH);                                  
        // if deactivated -> DONE
        else
            setState(eSTATE_DONE);                   
    }
     
    elbowSpeed = pELBus->getSO_JCONTROL_SPEED().getValue();
    tiltSpeed = pArmBus->getSO_TILT_SPEED().getValue();
}


void TiltKeeper::writeBus()
{  
    pVSBus->getCO_JCONTROL_ACCEL().request(outAccel, priority);
}


void TiltKeeper::showState()
{
    switch (getState())
    {
        case eSTATE_DONE:
            LOG4CXX_INFO(logger, ">> done");
            break;
                        
        case eSTATE_WATCH:
            LOG4CXX_INFO(logger, ">> watch");
            break;

        case eSTATE_DRIVE:
            LOG4CXX_INFO(logger, ">> drive");
            break;
    }   // end switch    
}

}