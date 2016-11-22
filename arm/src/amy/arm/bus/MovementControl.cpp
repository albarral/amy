/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/bus/MovementControl.h"

namespace amy
{
// Constructor
MovementControl::MovementControl ()
{    
    setElectricity(minElectricity);
    // null default values
    Kaccel = 0;
    Kspeed = 0;
    driverTolerance = 0;    
    driverSpeed = 0;
}

void MovementControl::setElectricity(int value)
{    
    std::lock_guard<std::mutex> locker(mutex);
    if (value >= minElectricity && value <= maxElectricity)
    {
        electricity = value;        
        //computeAcceleration();
    }
}

int MovementControl::getElectricity()
{
    std::lock_guard<std::mutex> locker(mutex);
    return electricity;    
}

//int MovementControl::getAccel()
//{
//    std::lock_guard<std::mutex> locker(mutex);
//    return accel;        
//}
//       
//// acceleration is a function of the required electricity
//void MovementControl::computeAcceleration()
//{
//    // quadratic function: accel proportional to E²
//    accel = 2*electricity*electricity;
//}

void MovementControl::setKaccelDriver(float value)
{    
    std::lock_guard<std::mutex> locker(mutex);
    Kaccel = value;
}

float MovementControl::getKaccelDriver()
{
    std::lock_guard<std::mutex> locker(mutex);
    return Kaccel;        
}

void MovementControl::setKspeedDriver(float value)
{    
    std::lock_guard<std::mutex> locker(mutex);
    Kspeed = value;
}

float MovementControl::getKspeedDriver()
{
    std::lock_guard<std::mutex> locker(mutex);
    return Kspeed;        
}

void MovementControl::setDriverTolerance(float value)
{    
    std::lock_guard<std::mutex> locker(mutex);
    driverTolerance = value;
}

float MovementControl::getDriverTolerance()
{
    std::lock_guard<std::mutex> locker(mutex);
    return driverTolerance;        
}

void MovementControl::setDriverSpeed(float value)
{    
    std::lock_guard<std::mutex> locker(mutex);
    driverSpeed = value;
}

float MovementControl::getDriverSpeed()
{
    std::lock_guard<std::mutex> locker(mutex);
    return driverSpeed;        
}

std::string MovementControl::toString()
{
    std::string desc = "MovementControl: [";
    desc += "Kaccel=" + std::to_string(Kaccel); 
    desc += ", Kspeed=" + std::to_string(Kspeed); 
    desc += ", driverTolerance=" + std::to_string(driverTolerance);
    desc += ", driverSpeed=" + std::to_string(driverSpeed) + "]";
    
    return desc;
}

}
