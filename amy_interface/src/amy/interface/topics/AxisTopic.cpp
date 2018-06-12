/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface/topics/AxisTopic.h"
#include "amy/interface/ArmNode.h"

namespace amy
{

AxisTopic::AxisTopic() : Topic(ArmNode::eARM_AXIS, ArmNode::ARM_AXIS)
{
    fillConcepts();    
}

void AxisTopic::fillConcepts()
{
    addCode(eAXIS_PAN_POS, AXIS_PAN_POS);
    addCode(eAXIS_TILT_POS, AXIS_TILT_POS);                         
    addCode(eAXIS_RAD_POS, AXIS_RAD_POS);                      
    addCode(eAXIS_PAN_SPEED, AXIS_PAN_SPEED);                   
    addCode(eAXIS_TILT_SPEED, AXIS_TILT_SPEED);                        
    addCode(eAXIS_RAD_SPEED, AXIS_RAD_SPEED);                        
    addCode(eAXIS_KEEP_TILT, AXIS_KEEP_TILT);                         
}
}