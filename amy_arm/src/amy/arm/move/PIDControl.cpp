/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/move/PIDControl.h"

namespace amy
{
PIDControl::PIDControl()
{
    // params default
    Kp = Ki = Kd = 0.0; 
    output = 0;
}

void PIDControl::init(float kp, float ki, float kd)
{
    Kp = kp;
    Ki = ki;
    Kd = kd;
};

float PIDControl::control(float error)
{
    // I+D control still pending ...
    output = Kp*error;    
    return output;
}

}