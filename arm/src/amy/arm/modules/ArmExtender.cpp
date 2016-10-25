/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/arm/modules/ArmExtender.h"

using namespace log4cxx;

namespace amy
{
ArmExtender::ArmExtender()
{
    modName = "ArmExtender";
}

//ArmExtender::~ArmExtender()
//{
//}

void ArmExtender::tune2Arm(int humerusLen, int radiusLen)
{
    oArmTrigonometry.setLengths(humerusLen, radiusLen);    
}

void ArmExtender::selectBusJoints()
{
    // connect to vertical shoulder
    pBusVS = &pBus->getBusVS();
    // connect to elbow
    pBusEL = &pBus->getBusEL();
}

void ArmExtender::senseBus()
{
    // get requested arm radius
    if (pBus->getCO_ARM_RADIUS().checkRequested())
    {
        targetPos = (int)pBus->getCO_ARM_RADIUS().getValue();    
        bnewMove = true;
    }
    
    // sense VS pos (soll value used here)
    istVS = pBusVS->getCO_JOINT_ANGLE().getValue();  
    
    // sense EL pos (soll value used here)
    istEL = pBusEL->getCO_JOINT_ANGLE().getValue();     
    
    // check if movement is blocked (due to reached joint limit)
    if (pBusEL->getSO_LIMIT_REACHED().getValue() != 0)
        blockedMove();

}

void ArmExtender::writeBus()
{  
    // send EL action
    pBusEL->getCO_JMOVER_ACCELERATION().request(sollAccel);
}


float ArmExtender::computeDistance()
{
    // store previous position
    istPosPrev = istPos;
    
    // compute wrist polar position
    oArmTrigonometry.computeWristPosition(istVS, istEL);    
    istPos = oArmTrigonometry.getArmRadius();
    
    istSpeed = (istPos - istPosPrev)/0.2;   // (tmp) in 5Hz executions
    
    return (targetPos - istPos);
}


void ArmExtender::senseInitialPosition()
{
    // sense VS pos (soll value used here)
    istVS = pBusVS->getCO_JOINT_ANGLE().getValue();  
    
    // sense EL pos (soll value used here)
    istEL = pBusEL->getCO_JOINT_ANGLE().getValue();     
    
    oArmTrigonometry.computeWristPosition(istVS, istEL);
    
    istPos = oArmTrigonometry.getArmRadius();
}
}