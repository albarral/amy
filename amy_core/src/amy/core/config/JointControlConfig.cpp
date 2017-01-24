/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/core/config/JointControlConfig.h"

namespace amy
{
// Constructor
JointControlConfig::JointControlConfig ()
{    
    // default values
    brakeAccel = 30;
    Kaccel = 0;
    Kspeed = 0;
    driverTolerance = 0;    
    driverSpeed = 0;
}

std::string JointControlConfig::toString()
{
    std::string desc = "JointControlSection: [";
    desc += "brakeAccel=" + std::to_string(brakeAccel); 
    desc += ", Kaccel=" + std::to_string(Kaccel); 
    desc += ", Kspeed=" + std::to_string(Kspeed); 
    desc += ", driverTolerance=" + std::to_string(driverTolerance);
    desc += ", driverSpeed=" + std::to_string(driverSpeed) + "]";
    
    return desc;
}

}
