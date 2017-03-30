/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/arm/move/JointAccelerator.h"

namespace amy
{

JointAccelerator::JointAccelerator()
{
    accel = 0.0;
    prevAngle = angle = 0.0;
}
       
void JointAccelerator::reset()
{
    oClick.reset();   
    accel = 0.0;
}

float JointAccelerator::move(float istAngle, float acceleration)
{
    touch(istAngle);
        
    // if accel, update avg speed
    if (accel != 0.0)
    {
        speed += accel*time;
    }

    // if avg speed, update position
    if (speed != 0.0)
        angle = istAngle + speed*time;      
    else
        angle = istAngle;
    
    // applied acceleration will affect next iteration
    accel = acceleration;
    return angle;
}


float JointAccelerator::brake(float istAngle, float deceleration)
{
    touch(istAngle);
    
    // brake in the opposite direction of the present speed
    int brakeDirection = (speed > 0.0) ? -1 : 1;    
    float acceleration = fabs(deceleration)*brakeDirection;
    
    // if some accel, update avg speed
    if (accel != 0.0)
    {
        float change= accel*time;        
        // limit change, not to surpass zero
        if (fabs(change) < fabs(speed))
            speed += change;
        else
            speed = 0.0;
    }

    // if some speed, update position
    if (speed != 0.0)
        angle = istAngle + speed*time;      
    else
        angle = istAngle;
    
    // applied deceleration will affect next iteration
    accel = acceleration;
    return angle;
}


void JointAccelerator::touch(float istAngle)
{
    // compute ellapsed time 
    oClick.read();
    oClick.start();    
    time = (float)oClick.getMillis()/1000.0;    
    
    // compute avg speed
    if (time != 0.0)
        speed = (istAngle - prevAngle)/time;
    else
        speed = 0.0;
    
    // store angle for next speed computation
    prevAngle = istAngle;
}

std::string JointAccelerator::toString()
{
    return "JointAccelerator: [speed=" + std::to_string(speed) + ", angle=" + std::to_string(angle) +  ", accel=" + std::to_string(accel) + "]";
}
}