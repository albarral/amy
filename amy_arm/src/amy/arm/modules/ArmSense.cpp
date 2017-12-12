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
    modName = "ArmSense";
    pBusPan = 0;
    pBusTilt = 0;
    pBusRadial = 0;
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
    
    oArmPolar.tune(oArm.getLenHumerus(), oArm.getLenRadius());
    pBusPan = &pArmBus->getPanBus();
    pBusTilt = &pArmBus->getTiltBus();
    pBusRadial = &pArmBus->getRadialBus();
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
        oArmPolar.sense(istHS, istVS, istELB);
        istPan = oArmPolar.getPanAngle();
        istTilt = oArmPolar.getTiltAngle();
        istRadius = oArmPolar.getRadius();        
        // and store joint positions (for next comparison)
        prevHS = istHS;
        prevVS = istVS;
        prevELB = istELB;
    }    
    
    oSpeedSensor3.sense(istPan, istTilt, istRadius);
    speedPan = oSpeedSensor3.getSpeed1();
    speedTilt = oSpeedSensor3.getSpeed2();
    speedRadius = oSpeedSensor3.getSpeed3();

    if (barmMoved)
    {
        LOG4CXX_DEBUG(logger, "(pan, tilt, radius) = (" << istPan << ", " << istTilt << ", " << istRadius << ") - (vpan, vtilt, vradius) = (" << speedPan << ", " << speedTilt << ", " << speedRadius << ")");
    }
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
    pBusPan->getSO_AXIS_POS().setValue(istPan);
    pBusTilt->getSO_AXIS_POS().setValue(istTilt);
    pBusRadial->getSO_AXIS_POS().setValue(istRadius);
    // inform speeds
    pBusPan->getSO_AXIS_SPEED().setValue(speedPan);
    pBusTilt->getSO_AXIS_SPEED().setValue(speedTilt);
    pBusRadial->getSO_AXIS_SPEED().setValue(speedRadius);
}

}