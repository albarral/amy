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
    oArmMath.setLengths(humerusLen, radiusLen);    
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
    
    // sense reached joint limits
    limitReached = pBusEL->getSO_JCONTROL_LIMIT_REACHED().getValue();
}

void ArmExtender::writeBus()
{  
    // send EL action
    pBusEL->getCO_JCONTROL_ACCEL().request(sollAccel);
}


float ArmExtender::computeDistance()
{
    // store previous position
    istPosPrev = istPos;
    
    // compute arm radius
    float radius = oArmMath.calcRadius(istEL);    
    istPos = radius;
    
//    istSpeed = (istPos - istPosPrev)/0.2;   // (tmp) in 5Hz executions
    
    return (targetPos - istPos);
}


void ArmExtender::senseInitialPosition()
{
    // sense VS pos (soll value used here)
    istVS = pBusVS->getCO_JOINT_ANGLE().getValue();  
    
    // sense EL pos (soll value used here)
    istEL = pBusEL->getCO_JOINT_ANGLE().getValue();     
    
    float radius = oArmMath.calcRadius(istEL);    
    istPos = radius;
}
}