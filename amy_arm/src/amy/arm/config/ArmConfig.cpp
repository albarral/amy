/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/config/ArmConfig.h"

namespace amy
{
// Constructor
ArmConfig::ArmConfig ()
{    
    // JointDriver modules
    brakeAccel = 30;
    // AxisDriver modules
    driverKaccel = 4.0;
    driverKspeed = 2.0;
    driverTolerance = 0.05;    
    driverSpeed = 120.0;
    // PID constants for TiltKeeper module
    PIDTiltKeeper[0] = 4.0; // P
    PIDTiltKeeper[1] = 0.0; // I   
    PIDTiltKeeper[2] = 2.0; // D        
    // PID constants for Racer module
    PIDRacer[0] = 4.0; // P
    PIDRacer[1] = 0.0; // I   
    PIDRacer[2] = 2.0; // D        
    
    // control priorities
    priority4TiltKeeper = 1;
    priority4AxisDrivers = 2;
    priority4AxisRacers = 3;
}

std::string ArmConfig::toString()
{
    std::string desc = "ArmConfig: [";
    desc += "brakeAccel=" + std::to_string(brakeAccel); 
    desc += ", driverKaccel=" + std::to_string(driverKaccel); 
    desc += ", driverKspeed=" + std::to_string(driverKspeed); 
    desc += ", driverTolerance=" + std::to_string(driverTolerance);
    desc += ", driverSpeed=" + std::to_string(driverSpeed) + "]";
    
    return desc;
}

}
