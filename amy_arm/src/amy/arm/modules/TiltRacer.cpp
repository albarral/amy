/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/TiltRacer.h"

using namespace log4cxx;

namespace amy
{
TiltRacer::TiltRacer()
{
    modName = "TiltRacer";       
    pBusTilt = 0;
    pVSBus = 0;
}

void TiltRacer::setControlledJoint()
{  
    pBusTilt = &pArmBus->getTiltBus();
    // controlled joint is VS
    pVSBus = &pArmBus->getBusVS();
}
       
void TiltRacer::senseBus()
{
    // if primary tilt speed requested -> NEWMOVE
    if (pBusTilt->getCO_AXIS_SPEED().checkRequested())
    {
        speed1 = pBusTilt->getCO_AXIS_SPEED().getValue();
        updateTargetSpeed();
        setState(eSTATE_NEWMOVE);   
    }
    // if secondary tilt speed requested -> NEWMOVE
    if (pBusTilt->getCO_AXIS_SPEED2().checkRequested())
    {
        speed2 = pBusTilt->getCO_AXIS_SPEED2().getValue();
        updateTargetSpeed();
        if (getState() == eSTATE_DONE)
            setState(eSTATE_NEWMOVE);   
    }
    
    // sense tilt speed
    axisSpeed= pBusTilt->getSO_AXIS_SPEED().getValue();    
    // sense reached VS limit
    jointLimit = pVSBus->getSO_JOINT_LIMIT_REACHED().getValue();
}

void TiltRacer::writeBus()
{  
    // control VS joint
    pVSBus->getCO_JOINT_ACCEL().request(outAccel, priority);
}

}