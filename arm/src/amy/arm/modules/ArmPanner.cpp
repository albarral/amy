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
    // on pan request -> new move
    if (pBus->getCO_ARM_PAN().checkRequested())
    {
        targetPos = (int)pBus->getCO_ARM_PAN().getValue();    
        bnewRequest = true;
    }
    
    // get real arm pan
    // TEMP: ArmPosition module not created yet.
    if (!ArmConfig::isArmPositionModuleWorking())
    {
        // Till then, arm pan read from HS angle
        istPos = pJointBus->getSO_IST_ANGLE().getValue();        
    }
    else    
        istPos = pBus->getSO_ARM_PAN().getValue();  
    
    // get commanded joint speed
    sollSpeed = pJointBus->getCO_JCONTROL_SPEED().getValue();
    // check if movement blocked (due to reached joint limit)
    if (pJointBus->getSO_LIMIT_REACHED().getValue() != 0)
        blockedMove();
    
    accel0 = pMovementControl->getAccel();
}


void ArmPanner::writeBus()
{  
    // send HS action
    pJointBus->getCO_JMOVER_ACTION().request(outAction);
    pJointBus->getCO_JMOVER_ACCELERATION().request(accel);
}

}