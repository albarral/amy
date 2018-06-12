/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface/ArmNode.h"
#include "amy/interface/topics/JointTopic.h"
#include "amy/interface/topics/AxisTopic.h"
#include "amy/interface/topics/CyclicTopic.h"
#include "tron2/robot/common/ExtraTopic.h"
#include "tron2/robot/RobotSystem.h"

namespace amy
{    
const std::string ArmNode::ARM_JOINT = "joint";
const std::string ArmNode::ARM_AXIS = "axis";
const std::string ArmNode::ARM_CYCLIC = "cyclic";

ArmNode::ArmNode() : tron2::Node(tron2::RobotSystem::eNODE_ARM, tron2::RobotSystem::ARM_NODE)
{
    fillTopics();
}

void ArmNode::fillTopics()
{
    // build topics map
    addCode(eARM_JOINT, ARM_JOINT);
    addCode(eARM_AXIS, ARM_AXIS);
    addCode(eARM_CYCLIC, ARM_CYCLIC);
    addCode(tron2::Node::eEXTRA_TOPIC, tron2::Node::EXTRA_TOPIC);
}

tron2::Topic* ArmNode::getTopic4Channel(int channel)
{                
    switch (channel)
    {
        case eARM_JOINTS_CHANNEL:
        {
            return new JointTopic();
            break;
        }            
        case eARM_AXES_CHANNEL: 
        {
            return new AxisTopic();
            break;
        }            
        case eARM_CYCLER1_CHANNEL: 
        case eARM_CYCLER2_CHANNEL: 
        {
            return new CyclicTopic();
            break;
        }            
        case eARM_EXTRA_CHANNEL: 
        {
            return new tron2::ExtraTopic();
            break;
        }            
        default:
            return nullptr;
    }        
}        
}