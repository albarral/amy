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
    pVSBus = 0;
}

void TiltRacer::setControlledJoint()
{
    // controlled joint is HS
    pVSBus = &pArmBus->getBusVS();
}
       
void TiltRacer::senseBus()
{
    // if tilt speed requested -> NEWMOVE
    if (pArmBus->getCO_TILT_SPEED().checkRequested())
    {
        targetSpeed = pArmBus->getCO_TILT_SPEED().getValue();
        setState(eSTATE_NEWMOVE);   
    }
    
    // sense tilt speed
    axisSpeed= pArmBus->getSO_TILT_SPEED().getValue();    
    // sense reached VS limit
    jointLimit = pVSBus->getSO_JCONTROL_LIMIT_REACHED().getValue();
}

void TiltRacer::writeBus()
{  
    // control VS joint
    pVSBus->getCO_JCONTROL_ACCEL().request(outAccel, priority);
}

}