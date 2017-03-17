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
    pBusRadial = 0;
    pELBus = 0;
}

void RadialRacer::setControlledJoint()
{
    pBusRadial = &pArmBus->getRadialBus();
    // controlled joint is ELB
    pELBus = &pArmBus->getBusEL();
}
       
void RadialRacer::senseBus()
{
    // if radial speed requested -> NEWMOVE
    if (pBusRadial->getCO_AXIS_SPEED().checkRequested())
    {
        targetSpeed = pBusRadial->getCO_AXIS_SPEED().getValue();
        setState(eSTATE_NEWMOVE);   
    }
    
    // sense radial speed
    axisSpeed= pBusRadial->getSO_AXIS_SPEED().getValue();    
    // sense reached ELB limit
    jointLimit = pELBus->getSO_JCONTROL_LIMIT_REACHED().getValue();
}

void RadialRacer::writeBus()
{  
    // control ELB joint
    pELBus->getCO_JCONTROL_ACCEL().request(outAccel, priority);
}

}