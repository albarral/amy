/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/move/SpeedControl.h"

namespace amy
{
SpeedControl::SpeedControl()
{
    targetSpeed = 0.0;
    blocked = false;
    outAccel = 0.0;
}

//SpeedControl::~SpeedControl()
//{
//}

void SpeedControl::init(float Kp, float Ki, float Kd)
{
    oPIDControl.init(Kp, Ki, Kd);
}                    

void SpeedControl::restart()
{
    oPIDControl.reset();
    blocked = false;
    outAccel = 0.0;
}

float SpeedControl::move(float istSpeed, int jointLimit)
{
    // compute movement acceleration
    outAccel = oPIDControl.control(targetSpeed - istSpeed);              

    // check if movement is blocked (pushing beyond the joint's limit)
    if (jointLimit != 0 && targetSpeed != 0.0)
        blocked = (targetSpeed > 0.0 && jointLimit > 0) || (targetSpeed < 0.0 && jointLimit < 0);        
    // no limit reached or no movement required
    else 
        blocked = false;    
    
    return outAccel;
}

std::string SpeedControl::toString()
{
    return "SpeedControl [target=" + std::to_string(targetSpeed) + ", blocked=" + std::to_string(blocked) 
            + ", accel=" + std::to_string(outAccel) + "]";
}


}