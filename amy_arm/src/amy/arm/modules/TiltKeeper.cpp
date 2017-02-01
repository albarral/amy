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
    bKeepMode = false;
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
        
    switch (getState())
    {
        case eSTATE_DRIVE:
            
            if (!bKeepMode)
                setState(eSTATE_DONE);
            else
            {
                float speedDeviation = -tiltSpeed;
                outAccel = oPIDControl.control(speedDeviation);      
                //if (outAccel != 0)
                {
                    LOG4CXX_INFO(logger, "outAccel = " << outAccel << ", tiltSpeed = " << tiltSpeed);
                    writeBus();
                }
            }
            break;  
            
        case eSTATE_DONE:

            if (bKeepMode)
                setState(eSTATE_DRIVE);
            break;
    }
}

void TiltKeeper::senseBus()
{
//    if (pArmBus->getCO_KEEP_TILT().checkRequested())
//    {
//        bKeepMode = pArmBus->getCO_KEEP_TILT().getValue();
//    }
    // TEMP for test
    bKeepMode = true;

    tiltSpeed = pArmBus->getSO_TILT_SPEED().getValue();
}


void TiltKeeper::writeBus()
{  
    pVSBus->getCO_JCONTROL_ACCEL().request(outAccel, priority);
}

}