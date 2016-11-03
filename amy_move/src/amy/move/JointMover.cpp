/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/move/JointMover.h"

namespace amy
{

JointMover::JointMover()
{
    accel = accel_ms = speed = angle = 0.0;
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
    accel_ms = value/1000;
}

void JointMover::setSpeed(float value)
{
    // ignore previous accel
    accel = accel_ms = 0.0;
    speed = value;
    speed_ms = value/1000;
}
                    
void JointMover::setAngle(float value)
{
    // ignore previous accel & speed
    accel = accel_ms = 0.0;
    speed = 0.0;
    limitAngle(value);
}

void JointMover::go()
{
    // compute ellapsed time
    oClick.read();
    oClick.start();

    // if no speed, no position change
    if (speed_ms == 0.0)
        return;

    int millis = oClick.getMillis();
    
    // update speed 
    if (accel_ms != 0.0)
    {
        speed += (float)(accel_ms*millis);
        speed_ms = speed/1000;
    }

    // update angle
    angle += (float)(speed_ms*millis);      
    
    // limit angle to joint's range
    limitAngle(angle);
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
}