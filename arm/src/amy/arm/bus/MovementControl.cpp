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
}

void MovementControl::setElectricity(int value)
{    
    std::lock_guard<std::mutex> locker(mutex);
    if (value >= minElectricity && value <= maxElectricity)
    {
        electricity = value;        
        computeAcceleration();
    }
}

int MovementControl::getElectricity()
{
    std::lock_guard<std::mutex> locker(mutex);
    return electricity;    
}

int MovementControl::getAccel()
{
    std::lock_guard<std::mutex> locker(mutex);
    return accel;        
}
       
// acceleration is a function of the required electricity
void MovementControl::computeAcceleration()
{
    // quadratic function: accel proportional to E²
    accel = 2*electricity*electricity;
}

}
