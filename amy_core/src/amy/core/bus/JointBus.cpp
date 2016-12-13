/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/core/bus/JointBus.h"

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
    if (benabled)
    {
        std::string text = "JointBus[" + jointName +  "]\n" +
             "CO_JCONTROL_ACCEL: " + std::to_string(CO_JCONTROL_ACCEL.getRequested()) + " - " + std::to_string(CO_JCONTROL_ACCEL.getValue()) + "\n" +
             "CO_JOINT_ANGLE: " + std::to_string(CO_JOINT_ANGLE.getRequested()) + " - " + std::to_string(CO_JOINT_ANGLE.getValue()) + "\n" +
             "SO_IST_ANGLE: " + std::to_string(SO_IST_ANGLE.getValue()) + "\n" +
             "SO_REAL_SPEED: " + std::to_string(SO_JCONTROL_SPEED.getValue()) + "\n" +
             "SO_LIMIT_REACHED: " + std::to_string(SO_JCONTROL_LIMIT_REACHED.getValue()) + "\n";

        return text;
    }
    else
        return "";
}
}
