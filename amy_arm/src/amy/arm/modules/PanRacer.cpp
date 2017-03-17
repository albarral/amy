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
    // if pan speed requested -> NEWMOVE
    if (pBusPan->getCO_AXIS_SPEED().checkRequested())
    {
        targetSpeed = pBusPan->getCO_AXIS_SPEED().getValue();
        setState(eSTATE_NEWMOVE);                   
    }
    
    // sense pan speed
    axisSpeed= pBusPan->getSO_AXIS_SPEED().getValue();    
    // sense reached HS limit
    jointLimit = pHSBus->getSO_JCONTROL_LIMIT_REACHED().getValue();
}

void PanRacer::writeBus()
{  
    // control HS joint
    pHSBus->getCO_JCONTROL_ACCEL().request(outAccel, priority);
}

}