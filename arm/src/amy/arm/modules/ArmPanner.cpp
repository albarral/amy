/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/ArmPanner.h"
#include "amy/arm/config/ArmConfig.h"

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
    // TEMP: ArmPosition module not created yet.
    if (!ArmConfig::isArmPositionModuleWorking())
    {
        // Till then, arm pan read from HS angle
        istPos = pJointBus->getSO_IST_ANGLE().getValue();        
    }
    else    
        istPos = pBus->getSO_ARM_PAN().getValue();  
    
    // get real joint speed
    istSpeed = pJointBus->getSO_REAL_SPEED().getValue();     
}


void ArmPanner::writeBus()
{  
    // send HS action
    pJointBus->getCO_JMOVER_ACTION().request(outAction);
}

}