/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

//#include <cmath>

#include "amy/arm/util/ArmMath.h"

//#define PI 3.14159265

namespace amy
{
// computes distance needed to brake completely from given speed using uniform acceleration (understood as deacceleration)
// dbrake = v²/2a       
float ArmMath::computeBrakeDistance(float speed, float accel)
{    
     return speed*speed/(2*accel);  // degrees
}

float ArmMath::getMovementResolution(float speed, float freq)
{
    return speed/freq;  // degrees
}
}
