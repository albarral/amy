/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/test/ArmPanner2.h"
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
    // connect to horizontal shoulder
    pJointBus = &pBus->getBusHS();
}

void ArmPanner2::senseBus()
{
    // get requested pan
    if (pBus->getCO_ARM_PAN().checkRequested())
    {
        targetPos = (int)pBus->getCO_ARM_PAN().getValue();    
        bnewRequest = true;
    }

    // get requested time for move
    if (pBus->getCO_ARM_T4MOVE().checkRequested())
        time4move = pBus->getCO_ARM_T4MOVE().getValue();
    
    // sense arm pan
    if (!ArmConfig::isArmPositionModuleWorking())
    {
        // TEMP: ArmPosition module not created yet.
        // Till then, arm pan read from HS angle
        istPos = pJointBus->getSO_IST_ANGLE().getValue();        
    }
    else    
        istPos = pBus->getSO_ARM_PAN().getValue();  
    
    // sense joint speed (soll value used)
    sollSpeed = pJointBus->getCO_JCONTROL_SPEED().getValue();

    // sense blocked moves (reached joint limit)
    if (pJointBus->getSO_LIMIT_REACHED().getValue() != 0)
        blockedMove();

    // use central acceleration    
    maxAccel = pMovementControl->getAccel();
}


void ArmPanner2::writeBus()
{  
    // send HS acceleration
    pJointBus->getCO_JMOVER_ACCELERATION().request(accel);
}

}