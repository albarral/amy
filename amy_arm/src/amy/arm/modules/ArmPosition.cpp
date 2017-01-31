/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/ArmPosition.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmPosition::logger(Logger::getLogger("amy.arm"));

ArmPosition::ArmPosition()
{
    modName = "ArmPosition";
    pHSBus = 0;
    pVSBus = 0;
    pELBus = 0;
}

void ArmPosition::first()
{
    setState(eSTATE_GO);
    
    oAxesSensor.tune(oArm);
    pHSBus = &pArmBus->getBusHS();
    pVSBus = &pArmBus->getBusVS();
    pELBus = &pArmBus->getBusEL();
    
    log4cxx::NDC::push(modName);   	
}
                    

// computes the axes positions
void ArmPosition::loop()
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

void ArmPosition::senseBus()
{
    // soll values used here instead of ist values
    istHS = pHSBus->getCO_JOINT_ANGLE().getValue();
    istVS = pVSBus->getCO_JOINT_ANGLE().getValue();
    istELB = pELBus->getCO_JOINT_ANGLE().getValue();
}


void ArmPosition::writeBus()
{  
    pArmBus->getSO_ARM_PAN().setValue(istPan);
    pArmBus->getSO_ARM_TILT().setValue(istTilt);
    pArmBus->getSO_ARM_RADIUS().setValue(istRadius);
}

}