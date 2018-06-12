/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface/topics/JointTopic.h"
#include "amy/interface/ArmNode.h"

namespace amy
{

JointTopic::JointTopic() : Topic(ArmNode::eARM_JOINT, ArmNode::ARM_JOINT)
{    
    fillConcepts();    
}

void JointTopic::fillConcepts()
{
    addCode(eJOINT_HS_POS, JOINT_HS_POS);
    addCode(eJOINT_VS_POS, JOINT_VS_POS);                         
    addCode(eJOINT_ELB_POS, JOINT_ELB_POS);                      
    addCode(eJOINT_HWRI_POS, JOINT_HWRI_POS);                   
    addCode(eJOINT_VWRI_POS, JOINT_VWRI_POS);                        
}
}