/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/RadialRacer.h"

using namespace log4cxx;

namespace amy
{
RadialRacer::RadialRacer()
{
    modName = "RadialRacer";       
    pELBus = 0;
}

void RadialRacer::setControlledJoint()
{
    // controlled joint is ELB
    pELBus = &pArmBus->getBusEL();
}
       
void RadialRacer::senseBus()
{
    // if radial speed requested -> NEWMOVE
    if (pArmBus->getCO_RADIAL_SPEED().checkRequested())
    {
        targetSpeed = pArmBus->getCO_RADIAL_SPEED().getValue();
        setState(eSTATE_NEWMOVE);   
    }
    
    // sense radial speed
    axisSpeed= pArmBus->getSO_RADIAL_SPEED().getValue();    
    // sense reached ELB limit
    jointLimit = pELBus->getSO_JCONTROL_LIMIT_REACHED().getValue();
}

void RadialRacer::writeBus()
{  
    // control ELB joint
    pELBus->getCO_JCONTROL_ACCEL().request(outAccel, priority);
}

}