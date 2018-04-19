/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/core/config/AmyConfig.h"
#include "amy/core/robot/Joint.h"

namespace amy
{    
// Constructor
AmyConfig::AmyConfig ()
{    
    modulesFreq = 20;  
    
    listControlledJoints.push_back(Joint::eJOINT_HS);
    listControlledJoints.push_back(Joint::eJOINT_VS);
    listControlledJoints.push_back(Joint::eJOINT_ELB);
    listControlledJoints.push_back(Joint::eJOINT_VW);
}

AmyConfig::~AmyConfig()
{
    listControlledJoints.clear();
}
}

