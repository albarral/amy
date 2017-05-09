/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/PanRacer.h"

using namespace log4cxx;

namespace amy
{
PanRacer::PanRacer()
{
    modName = "PanRacer";    
    pBusPan = 0;
    pHSBus = 0;
}

void PanRacer::setControlledJoint()
{
    pBusPan = &pArmBus->getPanBus();
    // controlled joint is HS
    pHSBus = &pArmBus->getBusHS();
}
       
void PanRacer::senseBus()
{
    brequested = false;
    // if primary pan speed requested -> NEWMOVE
    if (pBusPan->getCO_AXIS_SPEED().checkRequested())
    {
        speed1 = pBusPan->getCO_AXIS_SPEED().getValue();
        brequested = true;
    }
    // if secondary pan speed requested -> NEWMOVE
    if (pBusPan->getCO_AXIS_SPEED2().checkRequested())
    {
        speed2 = pBusPan->getCO_AXIS_SPEED2().getValue();
        brequested = true;
    }
    
    // sense pan speed
    axisSpeed= pBusPan->getSO_AXIS_SPEED().getValue();    
    // sense reached HS limit
    jointLimit = pHSBus->getSO_JOINT_LIMIT_REACHED().getValue();
}

void PanRacer::writeBus()
{  
    // control HS joint
    pHSBus->getCO_JOINT_ACCEL().request(outAccel, priority);
}

}