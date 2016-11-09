/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/arm/util/JointModule.h"

namespace amy
{
JointModule::JointModule()
{
    modName = "JointModule";
    jointName = "";
    pJointBus = 0;
}

void JointModule::setTargetJoint(std::string name)
{
    jointName = name;
    modName = modName + "-" + jointName;
}

void JointModule::connect(ArmBus& oArmBus)
{
    // get the specific bus connection for the target joint
    if (!jointName.empty())
    {
        pJointBus = &oArmBus.getJointBus(jointName);
        // and the general bus connection
        ArmModule::connect(oArmBus);
    }    
}

}