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
    this->angle = angle;   
    this->tics = tics;     
    this->vmax = maxSpeed;         
    // logic
    xmove = 0;
    ymove = 0;
    vx = 0;
    vy = 0;
}

}
