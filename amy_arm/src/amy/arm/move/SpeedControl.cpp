/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/move/SpeedControl.h"

namespace amy
{
SpeedControl::SpeedControl()
{
    // params default
    Kaccel = 1.0; 
    //speedTolerance = 0.10;
    outAccel = 0;
}

void SpeedControl::init(float kaccel, float speedTolerance)
{
    Kaccel = kaccel; 
    //this->speedTolerance = speedTolerance;
};

void SpeedControl::newMove(float speed)
{
    sollSpeed = speed;
    // new move requested
    oClick.reset();
    bjustStarted = true;
}

float SpeedControl::drive(float istAngle)
{    
    // compute ellapsed time 
    oClick.read();
    oClick.start();        
        
    // first step
    if (bjustStarted)
    {        
        // speed can't be measured on first step
        istSpeed = 0.0;
    }  
    // next steps
    else
    {
        // compute joint speed
        float time = (float)oClick.getMillis()/1000;
        istSpeed = (istAngle - prevAngle)/time;
    }
    
    prevAngle = istAngle;
    
    controlAccel();
    
    return outAccel;
}

       
// gets the proper acceleration to reach the target speed
void SpeedControl::controlAccel()
{    
    // acceleration is proportional to speed error
    outAccel = Kaccel*(sollSpeed - istSpeed);
}

std::string SpeedControl::toString()
{
    return "SpeedControl [ sollSpeed=" + std::to_string(sollSpeed) + " istSpeed=" + std::to_string(istSpeed) 
            + ", istAngle=" + std::to_string(prevAngle) + ", accel=" + std::to_string(outAccel) + "]";
}
}