/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/config/AmyArmConfig.h"

namespace amy
{
// Constructor
AmyArmConfig::AmyArmConfig ()
{    
    // JointDriver modules
    brakeAccel = 30;
    // AxisDriver modules
    driverKaccel = 4.0;
    driverKspeed = 3.0;
    driverTolerance = 0.05;    
    driverSpeed = 120.0;
    // TiltKeeper module
    tiltKeeperPID[0] = 4.0; // P
    tiltKeeperPID[1] = 0.0; // I   
    tiltKeeperPID[2] = 2.0; // D            
}

std::string AmyArmConfig::toString()
{
    std::string desc = "AmyArmConfig: [";
    desc += "brakeAccel=" + std::to_string(brakeAccel); 
    desc += ", driverKaccel=" + std::to_string(driverKaccel); 
    desc += ", driverKspeed=" + std::to_string(driverKspeed); 
    desc += ", driverTolerance=" + std::to_string(driverTolerance);
    desc += ", driverSpeed=" + std::to_string(driverSpeed) + "]";
    
    return desc;
}

}
