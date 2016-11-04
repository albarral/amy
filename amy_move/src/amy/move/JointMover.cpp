/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/move/JointMover.h"

namespace amy
{

JointMover::JointMover()
{
    accel = 0.0;
    speed = avgSpeed = 0.0;
    angle = 0.0;
    blimitReached = false;
    lowLimit = highLimit = 0;
}
       
void JointMover::init(int lowPos, int highPos)
{
    if (lowPos < highPos)
    {
        lowLimit = lowPos;
        highLimit = highPos;        
    }
}

void JointMover::setAccel(float value)
{
    accel = value;
}

void JointMover::setSpeed(float value)
{
    // ignore previous accel
    accel = 0.0;
    speed = value;
    avgSpeed = value;
}
                    
void JointMover::setAngle(float value)
{
    // ignore previous accel & speed
    accel = 0.0;
    speed = 0.0;
    avgSpeed = 0.0;
    limitAngle(value);
}

void JointMover::go()
{
    // compute ellapsed time (secs))
    oClick.read();
    oClick.start();    
    float time = (float)oClick.getMillis()/1000;    
    
    // if some accel, update final & average speeds
    if (accel != 0.0)
    {
        float speedChange = accel*time;
        avgSpeed = speed + 0.5*speedChange;
        speed += speedChange;
    }

    // if some speed, update position
    if (avgSpeed != 0.0)
    {
        angle += avgSpeed*time;      
        // limit angle to joint's range
        limitAngle(angle);
    }
}


void JointMover::limitAngle(float value)
{
    if (value < lowLimit) 
    {
        angle = lowLimit;
        blimitReached = true;
    }
    else if (value > highLimit)
    {
        angle = highLimit;
        blimitReached = true;
    }
    else 
    {
        angle = value;        
        blimitReached = false;
    }    
}

std::string JointMover::toString()
{
    return "JointMover: [accel=" + std::to_string(accel) + ", speed=" + std::to_string(speed) + ", angle=" + std::to_string(angle) + ", limit reached=" + std::to_string(blimitReached) + "]";
}
}