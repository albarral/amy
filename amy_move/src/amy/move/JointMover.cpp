/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/move/JointMover.h"

namespace amy
{

JointMover::JointMover()
{
    accel = 0.0;
    speed = avgSpeed = 0.0;
    angle = 0.0;
}
       
void JointMover::iddle()
{
    oClick.reset();   
    if (speed != 0.0)
        speed = 0.0;
}

float JointMover::move(float acceleration, float istAngle)
{
    // compute ellapsed time 
    oClick.read();
    oClick.start();        

    float time = (float)oClick.getMillis()/1000;    
    
    accel = acceleration;
    angle = istAngle;
    
    // if some accel, update speed
    if (accel != 0.0)
    {
        float speedChange = accel*time;
        speed += speedChange;
        // use average speed for position computation
        avgSpeed = speed - 0.5*speedChange;
    }

    // if some speed, update position
    if (avgSpeed != 0.0)
        angle += avgSpeed*time;      
    
    return angle;
}


float JointMover::brake(float deceleration, float istAngle)
{
    // compute ellapsed time 
    oClick.read();
    oClick.start();        

    float time = (float)oClick.getMillis()/1000;    

    // brake in the opposite direction of the present speed
    int brakeDirection = (speed > 0.0) ? -1 : 1;
    
    accel = fabs(deceleration)*brakeDirection;
    angle = istAngle;
    
    // if some accel, update speed
    if (accel != 0.0)
    {
        float speedChange = accel*time;
        // update speed 
        if (fabs(speedChange) < fabs(speed))
            speed += speedChange;
        // or vanish it if near enough
        else
            speed = 0;
        // use average speed for position computation        
        avgSpeed = speed - 0.5*speedChange;
    }

    // if some speed, update position
    if (avgSpeed != 0.0)
        angle += avgSpeed*time;      
    
    return angle;
}

std::string JointMover::toString()
{
    return "JointMover: [accel=" + std::to_string(accel) + ", speed=" + std::to_string(speed) + ", angle=" + std::to_string(angle) +  "]";
}
}