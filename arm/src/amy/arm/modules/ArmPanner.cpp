/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/ArmPanner.h"

using namespace log4cxx;

namespace amy
{
ArmPanner::ArmPanner()
{
    modName = "ArmPanner";
}

//ArmPanner::~ArmPanner()
//{
//}

void ArmPanner::selectBusJoint()
{
    // connect to horizontal shoulder
    pJointBus = &pBus->getBusHS();
}

void ArmPanner::senseBus()
{
    // get requested arm pan
    if (pBus->getCO_ARM_PAN().checkRequested())
        targetPos = (int)pBus->getCO_ARM_PAN().getValue();    
    // get real arm pan
    istPos = pBus->getSO_ARM_PAN().getValue();  
    // get real pan speed
    istSpeed = pJointBus->getCO_JCONTROL_SPEED().getValue();     
}


void ArmPanner::writeBus()
{  
    // send HS action
    pJointBus->getCO_JMOVER_ACTION().request(outAction);
}

}