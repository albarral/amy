/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/arm/move/JointDriver.h"

namespace amy
{
JointDriver::JointDriver()
{
    // params default
    Kaccel = 1.0; 
    Kspeed = 1.0;                 
    posTolerance = 0.10;
    maxSpeed = 20.0;
    // controls default
    outAccel = 0;
    moveSign = 0;
    state = JointDriver::eSTATE_DONE;
}

//JointDriver2::~JointDriver2()
//{
//}

void JointDriver::init(float kaccel, float kspeed, float posTolerance, float maxSpeed)
{
    Kaccel = kaccel; 
    Kspeed = kspeed;                 
    this->posTolerance = posTolerance;
    this->maxSpeed = fabs(maxSpeed);    // assure absolute value
};

void JointDriver::setTarget(float angle)
{
    targetAngle = angle;
    // new move requested
    oClick.reset();
    state = eSTATE_DRIVE;
    steps = 0;
}

float JointDriver::drive(float istAngle)
{    
    // compute ellapsed time 
    oClick.read();
    oClick.start();        
    
    // compute distance to target
    float dist = targetAngle - istAngle;
    
    // first step
    if (steps == 0)
    {
        // set movement direction
        moveSign = (dist > 0 ? 1: -1);

        // compute arrival distance (same sign as initial distance)
        arrivalDist = posTolerance*dist;
        // lower limit arrival distance to minimum resolution
        if (fabs(arrivalDist) < minResolution)
            arrivalDist = (arrivalDist > 0 ? minResolution : -minResolution);      
        
        // speed can't be measured on first step
        istSpeed = 0.0;
    }  
    // next steps
    else
    {
        // compute joint speed
        float time = (float)oClick.getMillis()/1000;
        istSpeed = (istAngle - this->istAngle)/time;
    }
    
    this->istAngle = istAngle;
    
    // handle transitions
    switch (state)
    {
        case eSTATE_DRIVE:
            
            // when the drive crosses the arrival point -> arrived
            if ((moveSign > 0 && dist < arrivalDist) || (moveSign < 0 && dist > arrivalDist))                
                state = eSTATE_ARRIVED; 
            break;

        case eSTATE_ARRIVED:
       
            // in target -> done
            if ((int)istSpeed == 0)
                state = eSTATE_DONE;                                
            break;
    }   // end switch        
                
    // perform control    
    switch (getState())
    {
        case eSTATE_DRIVE:
            
            // drive at proportional speed
            controlSpeed(dist);
            controlAccel();
            break;

        case eSTATE_ARRIVED:
       
            // stop joint 
            targetSpeed = 0.0;
            controlAccel();
            break;
            
        case eSTATE_DONE:
       
            // nothing done
            outAccel = 0.0;
            break;            
    }   // end switch            
        
    steps++;
    
    return outAccel;
}


// computes the target speed of the movement
void JointDriver::controlSpeed(float dist)
{        
    // speed is proportional to distance from target
    targetSpeed = Kspeed*dist;
        
    // but limited 
    if (fabs(targetSpeed) > maxSpeed)        
        targetSpeed = (targetSpeed > 0 ? maxSpeed : -maxSpeed);
}
       
// gets the proper acceleration to reach the target speed
void JointDriver::controlAccel()
{    
    // acceleration is proportional to speed error
    outAccel = Kaccel*(targetSpeed - istSpeed);
}

std::string JointDriver::toString()
{
    return "JointDriver [target=" + std::to_string(targetAngle) + ", ist=" + std::to_string(istAngle) 
            + " targetSpeed=" + std::to_string(targetSpeed) + " istSpeed=" + std::to_string(istSpeed) 
            + ", state=" + std::to_string(state) + ", accel=" + std::to_string(outAccel) + "]";
}

std::string JointDriver::paramsToString()
{
    return "JointDriver params [Kaccel=" + std::to_string(Kaccel) + ", Kspeed=" + std::to_string(Kspeed) 
            + " posTolerance=" + std::to_string(posTolerance) + " maxSpeed=" + std::to_string(maxSpeed) + "]";
}
}