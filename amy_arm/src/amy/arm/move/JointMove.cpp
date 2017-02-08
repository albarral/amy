/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/arm/move/JointMove.h"

namespace amy
{

JointMove::JointMove()
{
    accel = 0.0;
    finalSpeed = speed = 0.0;
    angle = 0.0;
}
       
void JointMove::iddle()
{
    oClick.reset();   
    if (finalSpeed != 0.0)
        finalSpeed = 0.0;
}

float JointMove::move(float acceleration, float istAngle)
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
        finalSpeed += speedChange;
        // use average speed for position computation
        speed = finalSpeed - 0.5*speedChange;
    }

    // if some speed, update position
    if (speed != 0.0)
        angle += speed*time;      
    
    return angle;
}


float JointMove::brake(float deceleration, float istAngle)
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

        // change can never be higher than speed
        if (fabs(speedChange) > fabs(finalSpeed))
            speedChange = -finalSpeed;

        // update speed             
        finalSpeed += speedChange;
        // use average speed for position computation        
        speed = finalSpeed - 0.5*speedChange;
    }

    // if some speed, update position
    if (speed != 0.0)
        angle += speed*time;      
    
    return angle;
}

std::string JointMove::toString()
{
    return "JointMove: [accel=" + std::to_string(accel) + ", speed=" + std::to_string(speed) + ", angle=" + std::to_string(angle) +  "]";
}
}