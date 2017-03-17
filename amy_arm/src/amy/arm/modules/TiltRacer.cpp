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
    // if tilt speed requested -> NEWMOVE
    if (pBusTilt->getCO_AXIS_SPEED().checkRequested())
    {
        targetSpeed = pBusTilt->getCO_AXIS_SPEED().getValue();
        setState(eSTATE_NEWMOVE);   
    }
    
    // sense tilt speed
    axisSpeed= pBusTilt->getSO_AXIS_SPEED().getValue();    
    // sense reached VS limit
    jointLimit = pVSBus->getSO_JCONTROL_LIMIT_REACHED().getValue();
}

void TiltRacer::writeBus()
{  
    // control VS joint
    pVSBus->getCO_JCONTROL_ACCEL().request(outAccel, priority);
}

}