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
    bActive = false;
    priority = 1;
    pVSBus = 0;
}
 

void TiltKeeper::first()
{
    setState(eSTATE_DONE);
    
    pVSBus = &pArmBus->getBusVS();
    float Ka = 4.0; // SHOULD BE OBTAINED FROM config file
    oPIDControl.init(Ka, 0.0, 0.0);
    
    log4cxx::NDC::push(modName);   	
}
                    

// computes the axes positions
void TiltKeeper::loop()
{    
    senseBus();

    if (!bActive)
    {
        // if module deactivated now -> DONE
        if (getState() != eSTATE_DONE)
        {
            setState(eSTATE_DONE);                   
            showState();
        }
        // if deactivated skip anyway 
        return;
    }

    // TRANSITIONS (activated module)
    switch (getState())
    {        
        case eSTATE_WATCH:     

            // if tilt changing -> DRIVE
            if (tiltSpeed != 0.0)
                setState(eSTATE_DRIVE);
            break;  

        case eSTATE_DRIVE:

            // if tilt stable -> WATCH
            if (tiltSpeed == 0.0)
                setState(eSTATE_WATCH);                            
            break;              

        case eSTATE_DONE:            

            // if DONE (activated) -> WATCH
            setState(eSTATE_WATCH);                            
            break;
    }
    
    if (isStateChanged())
        showState();

    // ACTIONS
    // if DRIVE: move VS
    if (getState() == eSTATE_DRIVE)
    {
        // PID control with error = 0 - tiltSpeed
        outAccel = oPIDControl.control(-tiltSpeed);              
        writeBus();
        LOG4CXX_INFO(logger, "outAccel = " << outAccel << ", tiltSpeed = " << tiltSpeed);
    }
}


void TiltKeeper::senseBus()
{
    if (pArmBus->getCO_KEEP_TILT().checkRequested())
    {
        bActive = pArmBus->getCO_KEEP_TILT().getValue();
    }
    // TEMP for test
    bActive = true;

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