/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/core/config/AmyConfig.h"
#include "amy/core/robot/Arm.h"

namespace amy
{    
// Constructor
AmyConfig::AmyConfig ()
{    
    modulesFreq = 10;  // 10 Hz
    
    listControlledJoints.push_back(Arm::horizontal_shoulder);
    listControlledJoints.push_back(Arm::vertical_shoulder);
    listControlledJoints.push_back(Arm::elbow);
    listControlledJoints.push_back(Arm::vertical_wrist);
}

AmyConfig::~AmyConfig()
{
    listControlledJoints.clear();
}
}

