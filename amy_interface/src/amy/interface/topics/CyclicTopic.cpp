/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface/topics/CyclicTopic.h"
#include "amy/interface/ArmNode.h"

namespace amy
{

CyclicTopic::CyclicTopic() : Topic(ArmNode::eARM_CYCLIC, ArmNode::ARM_CYCLIC)
{
    fillConcepts();    
}

void CyclicTopic::fillConcepts()
{
    addCode(eCYCLIC_MAIN_FREQ, CYCLIC_MAIN_FREQ);
    addCode(eCYCLIC_MAIN_AMP, CYCLIC_MAIN_AMP);                         
    addCode(eCYCLIC_MAIN_ANGLE, CYCLIC_MAIN_ANGLE);                      
    addCode(eCYCLIC_MAIN_PHASE, CYCLIC_MAIN_PHASE);                   
    addCode(eCYCLIC_SEC_FREQ, CYCLIC_SEC_FREQ);
    addCode(eCYCLIC_SEC_AMP, CYCLIC_SEC_AMP);                         
    addCode(eCYCLIC_SEC_ANGLE, CYCLIC_SEC_ANGLE);                      
    addCode(eCYCLIC_SEC_PHASE, CYCLIC_SEC_PHASE);                   
    addCode(eCYCLIC_ACTION, CYCLIC_ACTION);                        
}
}