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

}
