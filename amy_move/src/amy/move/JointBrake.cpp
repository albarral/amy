/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/move/JointBrake.h"

namespace amy
{

JointBrake::JointBrake()
{
    brakeAccel = brakeAccel_ms = 0.0;
    speed = 0.0;
}
       
void JointBrake::setBrakeAccel(float value)
{
    brakeAccel = value;
    brakeAccel_ms = value/1000.0;
}

void JointBrake::click()
{
    // compute ellapsed time
    oClick.read();
    oClick.start();        
}

void JointBrake::go(float istSpeed)
{
    // if some brakeAccel, update final & average speeds
    if (brakeAccel != 0.0)
    {
        // brake in the opposite direction of the present speed
        int brakeDirection = (istSpeed > 0.0) ? -1 : 1;
        float change = (float)(brakeDirection*brakeAccel_ms*oClick.getMillis());

        // update speed 
        if (fabs(change) < fabs(istSpeed))
            speed += change;
        // or vanish it if near enough
        else
            speed = 0;
    }
}

std::string JointBrake::toString()
{
    return "JointBrake: [brakeAccel=" + std::to_string(brakeAccel) + ", speed=" + std::to_string(speed) + "]";
}
}