/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/ArmPanner2.h"
#include "amy/arm/config/ArmConfig.h"

using namespace log4cxx;

namespace amy
{
ArmPanner2::ArmPanner2()
{
    modName = "ArmPanner2";
}

//ArmPanner2::~ArmPanner2()
//{
//}

void ArmPanner2::selectBusJoint()
{
    // connect to HS joint (horizontal shoulder)
    pJointBus = &pBus->getBusHS();
}

void ArmPanner2::senseBus()
{
    // get requested pan
    if (pBus->getCO_ARM_PAN().checkRequested())
    {
        targetPos = (int)pBus->getCO_ARM_PAN().getValue();    
        bnewMove = true;
    }

    // sense arm pan (soll value used here)
    istPos = pJointBus->getCO_JOINT_ANGLE().getValue();
    
    // sense joint speed (soll value used here)
    istSpeed = pJointBus->getCO_JCONTROL_SPEED().getValue();

    // check if movement is blocked (due to reached joint limit)
    if (pJointBus->getSO_LIMIT_REACHED().getValue() != 0)
        blockedMove();
}


void ArmPanner2::writeBus()
{  
    // send HS acceleration
    pJointBus->getCO_JMOVER_ACCELERATION().request(sollAccel);
}

float ArmPanner2::computeDistance()
{
    return (targetPos - istPos);
}
}