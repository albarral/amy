/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/config/ArmConfig.h"
#include "amy/robot/Arm.h"

namespace amy
{    
// Constructor
ArmConfig::ArmConfig ()
{    
    // TEMPORAL: all params should be read from a file    
    modulesFreq = 5;  // 5 Hz
    brakeAccel = 30;
    
    listControlledJoints.push_back(Arm::horizontal_shoulder);
    listControlledJoints.push_back(Arm::vertical_shoulder);
    listControlledJoints.push_back(Arm::elbow);
    listControlledJoints.push_back(Arm::vertical_wrist);
}

ArmConfig::~ArmConfig()
{
    listControlledJoints.clear();
}
}

