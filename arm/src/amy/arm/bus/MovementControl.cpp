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
    setTime4Move(maxTime4move);    
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

void MovementControl::setTime4Move(float value)
{
    std::lock_guard<std::mutex> locker(mutex);

    if (value >= minTime4move && value <= maxTime4move) 
        time4move = value;
}

int MovementControl::getElectricity()
{
    std::lock_guard<std::mutex> locker(mutex);
    return electricity;    
}

float MovementControl::getTime4Move()
{
    std::lock_guard<std::mutex> locker(mutex);
    return time4move;
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
