/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/PanRacer.h"

using namespace log4cxx;

namespace amy
{
PanRacer::PanRacer()
{
    modName = "PanRacer";   
    pHSBus = 0;
}

//PanRacer::~PanRacer()
//{
//}


void PanRacer::connectOutput()
{
    // connect to HS joint 
    pHSBus = &pArmBus->getBusHS();
}
       

void PanRacer::senseBus()
{
    // get requested pan
    if (pArmBus->getCO_PAN_SPEED().checkRequested())
    {
        targetSpeed = pArmBus->getCO_PAN_SPEED().getValue();  
        setState(eSTATE_GO);   
    }

    // sense pan speed
    istSpeed= pArmBus->getSO_PAN_SPEED().getValue();
    
    // sense reached HS limits
    jointLimit = pHSBus->getSO_JCONTROL_LIMIT_REACHED().getValue();
}

void PanRacer::writeBus()
{  
    pHSBus->getCO_JCONTROL_ACCEL().request(outAccel, priority);
}

}