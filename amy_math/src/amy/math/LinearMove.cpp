/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/math/LinearMove.h"
#include "amy/math/MathDefines.h"

namespace amy
{
LinearMove::LinearMove()
{
    angle = 0.0;
    cosA = 1.0;
    sinA = 0.0;
    vx = vy = 0.0;
}

void LinearMove::setAngle(float value)
{
    // convert to radians
    angle = value;
    float radians = angle * KPI_DIV_180;
    sinA = sin(radians);
    cosA = cos(radians);    
}

void LinearMove::compute(float speed)
{
    // vx = vA cos(a)
    // vy = vA sin(a);
    vx = speed*cosA;    
    vy = speed*sinA;  
}
}
