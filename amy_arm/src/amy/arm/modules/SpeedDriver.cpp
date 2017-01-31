/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/SpeedDriver.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr SpeedDriver::logger(Logger::getLogger("amy.arm"));

SpeedDriver::SpeedDriver()
{
    modName = "SpeedDriver";
    bKeepMode = false;
    priority = 2;
    pVSBus = 0;
}
 

void SpeedDriver::first()
{
    setState(eSTATE_DONE);
    
    pVSBus = &pArmBus->getBusVS();
    
    log4cxx::NDC::push(modName);   	
}
                    

// computes the axes positions
void SpeedDriver::loop()
{
    senseBus();
    
    // if joints positions changed
    if (istHS != prevHS || istVS != prevVS || istELB != prevELB)
    {
        // compute axes position
        oAxesSensor.computeAxes(istHS, istVS, istELB);
        istPan = oAxesSensor.getPanAngle();
        istTilt = oAxesSensor.getTiltAngle();
        istRadius = oAxesSensor.getRadius();
        // update bus values
        writeBus();        
        // and store joint positions (for next comparison)
        prevHS = istHS;
        prevVS = istVS;
        prevELB = istELB;

        LOG4CXX_INFO(logger, "pan = " << istPan << ", tilt = " << istTilt << ", radius = " << istRadius);
    }    
}

void SpeedDriver::senseBus()
{
    if (pArmBus->getCO_KEEP_TILT().checkRequested())
    {
        bKeepMode = pArmBus->getCO_KEEP_TILT().getValue();
    }

    istTilt = pArmBus->getSO_ARM_TILT();
}


void SpeedDriver::writeBus()
{  
    pArmBus->getSO_ARM_PAN().setValue(istPan);
    pArmBus->getSO_ARM_TILT().setValue(istTilt);
    pArmBus->getSO_ARM_RADIUS().setValue(istRadius);
}

}