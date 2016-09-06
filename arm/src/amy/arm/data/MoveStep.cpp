/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/data/MoveStep.h"

#define PI 3.14159265

namespace amy
{
MoveStep::MoveStep ()
{
    bcomputed = false;
    bstepEnding = false;    // by default not a step ending move
    angle = 0;   
    tics = 0;     
    vmax = 0; 
    // logic
    xmove = 0;
    ymove = 0;
    vx = 0;
    vy = 0;
}

MoveStep::MoveStep(int angle, int tics, int maxSpeed)
{
    bcomputed = false;
    bstepEnding = false;     // by default not a step ending move
    this->angle = angle;   
    this->tics = tics;     
    this->vmax = maxSpeed;         
    // logic
    xmove = 0;
    ymove = 0;
    vx = 0;
    vy = 0;
}

 void MoveStep::setStepEnding(int value)
 {
     xmove = value;
     ymove = value;
     bstepEnding = true;
 }
 
std::string MoveStep::getDescription()
{
    return "MoveStep:[angle=" + std::to_string(angle) +
            ", tics=" + std::to_string(tics) +
            ", vmax=" + std::to_string(vmax) +
            ", xmove=" + std::to_string(xmove) +
            ", ymove=" + std::to_string(ymove) +
            ", tics=" + std::to_string(tics) +
            ", vx=" + std::to_string(vx) +
            ", vy=" + std::to_string(vy) + "]"; 
}

}
