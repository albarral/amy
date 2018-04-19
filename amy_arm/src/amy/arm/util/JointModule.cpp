/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/util/JointModule.h"
#include "amy/core/robot/Joint.h"

namespace amy
{
JointModule::JointModule()
{
    modName = "JointModule";
    targetJoint = -1;
    pJointBus = 0;
}

void JointModule::setTargetJoint(int type)
{
    if (Joint::isValidType(type))
    {
        targetJoint = type;
        modName = modName + "-" + Joint::getName4Type(type);        
    }
}

void JointModule::connect(ArmBus& oArmBus)
{
    // get the specific bus connection for the target joint      
    switch (targetJoint)
    {
        case Joint::eJOINT_HS:
            pJointBus = &(oArmBus.getBusHS());
            break;
        case Joint::eJOINT_VS:
            pJointBus = &(oArmBus.getBusVS());
            break;
        case Joint::eJOINT_ELB:
            pJointBus = &(oArmBus.getBusEL());
            break;
        case Joint::eJOINT_HW:
            pJointBus = &(oArmBus.getBusHW());
            break;
        case Joint::eJOINT_VW:
            pJointBus = &(oArmBus.getBusVW());
            break;
    }
    // and the general bus connection
    ArmModule::connect(oArmBus);
}

}