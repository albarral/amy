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

void ArmExtender::selectBusJoint()
{
    // connect to elbow
    pJointBus = &pBus->getBusEL();
}

void ArmExtender::senseBus()
{
    // get requested arm radius
    if (pBus->getCO_ARM_RADIUS().checkRequested())
        targetPos = (int)pBus->getCO_ARM_RADIUS().getValue();    
    // get real arm radius
    istPos = pBus->getSO_ARM_RADIUS().getValue();  
    // get real elbow speed
    sollSpeed = pJointBus->getCO_JCONTROL_SPEED().getValue();     
}

void ArmExtender::writeBus()
{  
    // send EL action
    pJointBus->getCO_JMOVER_ACTION().request(outAction);
}

}