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

    oJointControlConfig.setBrakeAccel(30);
    oJointControlConfig.setKaccelDriver(4.0);
    oJointControlConfig.setKspeedDriver(2.0);
    oJointControlConfig.setDriverTolerance(0.05);
    oJointControlConfig.setDriverSpeed(120.0);
}

AmyConfig::~AmyConfig()
{
    listControlledJoints.clear();
}
}

