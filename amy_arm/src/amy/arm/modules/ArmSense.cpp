/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/ArmSense.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmSense::logger(Logger::getLogger("amy.arm"));

ArmSense::ArmSense()
{
    modName = "ArmPolarSensing";
    pHSBus = 0;
    pVSBus = 0;
    pELBus = 0;
}

void ArmSense::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}

void ArmSense::first()
{
    setState(eSTATE_GO);
    
    oArmPolarSensor.tune(oArm);
    pHSBus = &pArmBus->getBusHS();
    pVSBus = &pArmBus->getBusVS();
    pELBus = &pArmBus->getBusEL();
    
    log4cxx::NDC::push(modName);   	
}
                    
// computes the axes positions
void ArmSense::loop()
{
    senseBus();
    
    // check if arm has moved
    bool barmMoved = (istHS != prevHS || istVS != prevVS || istELB != prevELB);  
    
    // if arm has moved, compute polar position
    if (barmMoved)
    {
        // compute polar position
        oArmPolarSensor.sense(istHS, istVS, istELB);
        istPan = oArmPolarSensor.getPanAngle();
        istTilt = oArmPolarSensor.getTiltAngle();
        istRadius = oArmPolarSensor.getRadius();        
        // and store joint positions (for next comparison)
        prevHS = istHS;
        prevVS = istVS;
        prevELB = istELB;
    }    
    
    oSpeedSensor3.sense(istPan, istTilt, istRadius);
    speedPan = oSpeedSensor3.getSpeed1();
    speedTilt = oSpeedSensor3.getSpeed2();
    speedRadius = oSpeedSensor3.getSpeed3();

//    if (barmMoved)
//    {
//        LOG4CXX_INFO(logger, "(pan, tilt, radius) = (" << istPan << ", " << istTilt << ", " << istRadius << ") - (vpan, vtilt, vradius) = (" << speedPan << ", " << speedTilt << ", " << speedRadius << ")");
//    }
//    else
//        LOG4CXX_INFO(logger, "(pan, tilt, radius) = (" << istPan << ", " << istTilt << ", " << istRadius << ")");

    // update bus values
    writeBus();        
}

void ArmSense::senseBus()
{
    // soll values used here instead of ist values
    istHS = pHSBus->getCO_JOINT_ANGLE().getValue();
    istVS = pVSBus->getCO_JOINT_ANGLE().getValue();
    istELB = pELBus->getCO_JOINT_ANGLE().getValue();
}


void ArmSense::writeBus()
{  
    // inform positions
    pArmBus->getSO_ARM_PAN().setValue(istPan);
    pArmBus->getSO_ARM_TILT().setValue(istTilt);
    pArmBus->getSO_ARM_RADIUS().setValue(istRadius);
    // inform speeds
    pArmBus->getSO_PAN_SPEED().setValue(speedPan);
    pArmBus->getSO_TILT_SPEED().setValue(speedTilt);
    pArmBus->getSO_RADIAL_SPEED().setValue(speedRadius);
}

}