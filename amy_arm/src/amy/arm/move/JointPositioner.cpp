/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/arm/move/JointPositioner.h"

namespace amy
{
JointPositioner::JointPositioner()
{
    // params default
    Kaccel = 1.0; 
    Kspeed = 1.0;                 
    posTolerance = 0.10;
    maxSpeed = 20.0;
    // controls default
    outAccel = 0;
    moveSign = 0;
    state = JointPositioner::eSTATE_DONE;
}

//JointControl2::~JointControl2()
//{
//}

void JointPositioner::init(float kaccel, float kspeed, float posTolerance, float maxSpeed)
{
    Kaccel = kaccel; 
    Kspeed = kspeed;                 
    this->posTolerance = posTolerance;
    this->maxSpeed = fabs(maxSpeed);    // assure absolute value
};

void JointPositioner::setNewMove(float angle)
{
    targetAngle = angle;
    // new move requested
    oClick.reset();
    state = eSTATE_DRIVE;
    steps = 0;
}

float JointPositioner::drive(float istAngle)
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
        istSpeed = (istAngle - prevAngle)/time;
    }
    
    //store ist angle for iteration
    prevAngle = istAngle;
    
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
            sollSpeed = 0.0;
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
void JointPositioner::controlSpeed(float dist)
{        
    // speed is proportional to distance from target
    sollSpeed = Kspeed*dist;
        
    // but limited 
    if (fabs(sollSpeed) > maxSpeed)        
        sollSpeed = (sollSpeed > 0 ? maxSpeed : -maxSpeed);
}
       
// gets the proper acceleration to reach the target speed
void JointPositioner::controlAccel()
{    
    // acceleration is proportional to speed error
    outAccel = Kaccel*(sollSpeed - istSpeed);
}

std::string JointPositioner::toString()
{
    return "JointPositioner [target=" + std::to_string(targetAngle) + ", ist=" + std::to_string(prevAngle) 
            + " sollSpeed=" + std::to_string(sollSpeed) + " istSpeed=" + std::to_string(istSpeed) 
            + ", state=" + std::to_string(state) + ", accel=" + std::to_string(outAccel) + "]";
}

std::string JointPositioner::paramsToString()
{
    return "JointPositioner params [Kaccel=" + std::to_string(Kaccel) + ", Kspeed=" + std::to_string(Kspeed) 
            + " posTolerance=" + std::to_string(posTolerance) + " maxSpeed=" + std::to_string(maxSpeed) + "]";
}
}