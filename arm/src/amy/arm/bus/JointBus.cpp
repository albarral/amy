/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/bus/JointBus.h"

namespace amy
{
// Constructor
JointBus::JointBus ()
{    
    benabled = false;
}

void JointBus::init(std::string jointName)
{
    this->jointName = jointName;
    benabled = true;    
}

std::string JointBus::toString()
{
    std::string text = "JointBus[" + jointName +  "]\n" +
         "CO_JMOVER_ACTION: " + std::to_string(CO_JMOVER_ACTION.getValue()) + " - " + std::to_string(CO_JMOVER_ACTION.getRequested()) + "\n" +
         "CO_JCONTROL_SPEED: " + std::to_string(CO_JCONTROL_SPEED.getValue()) + " - " + std::to_string(CO_JCONTROL_SPEED.getRequested()) + "\n" +
         "CO_JOINT_ANGLE: " + std::to_string(CO_JOINT_ANGLE.getValue()) + " - " + std::to_string(CO_JOINT_ANGLE.getRequested()) + "\n" +
         "SO_IST_ANGLE: " + std::to_string(SO_IST_ANGLE.getValue()) + "\n" +
         "SO_REAL_SPEED: " + std::to_string(SO_REAL_SPEED.getValue()) + "\n" +
         "SO_LIMIT_REACHED: " + std::to_string(SO_LIMIT_REACHED.getValue()) + "\n";
    
    return text;
}
}
