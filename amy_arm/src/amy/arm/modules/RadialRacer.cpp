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

void RadialRacer::setSpecificConnections()
{
    pBusRadial = &pArmBus->getRadialBus();
    // controlled joint is ELB
    pELBus = &pArmBus->getBusEL();
}
       
void RadialRacer::senseBus()
{
    brequested = false;
    // if primary radial speed requested -> NEWMOVE
    if (pBusRadial->getCO_AXIS_SPEED().checkRequested())
    {
        speed1 = pBusRadial->getCO_AXIS_SPEED().getValue();
        brequested = true;
    }
    // if secondary radial speed requested -> NEWMOVE
    if (pBusRadial->getCO_AXIS_SPEED2().checkRequested())
    {
        speed2 = pBusRadial->getCO_AXIS_SPEED2().getValue();
        brequested = true;
    }
    
    // sense radial speed
    axisSpeed= pBusRadial->getSO_AXIS_SPEED().getValue();    
    // sense reached ELB limit
    jointLimit = pELBus->getSO_JOINT_LIMIT_REACHED().getValue();
}

void RadialRacer::writeBus()
{  
    // control ELB joint
    pELBus->getCO_JOINT_ACCEL().request(outAccel, priority);
}

}