/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/move/RadialDriver.h"
#include "JointDriver.h"

namespace amy
{
RadialDriver::RadialDriver()
{
    // params default
    workSign = -1; // default downside work plane
}

//RadialDriver2::~RadialDriver2()
//{
//}

void RadialDriver::setArmSize(int lenHumerus, int lenRadius)
{
    oArmMath.setLengths(lenHumerus, lenRadius);
};

void RadialDriver::workUp()
{
    workSign = 1;
}

void RadialDriver::workDown()
{
    workSign = -1;
}

void RadialDriver::setTargetRadius(float radius)
{    
    float elbowAngle = oArmMath.calcElbowAngle(radius);
    
    // set target in proper work plane
    elbowAngle = fabs(elbowAngle) * workSign;
    
    JointDriver::setTarget(elbowAngle);
}

//std::string RadialDriver::toString()
//{
//    return "RadialDriver:: [target=" + std::to_string(targetAngle) + ", ist=" + std::to_string(istAngle) 
//            + " targetSpeed=" + std::to_string(targetSpeed) + " istSpeed=" + std::to_string(istSpeed) 
//            + ", state=" + std::to_string(state) + ", accel=" + std::to_string(outAccel) + "]";
//}
//
//std::string RadialDriver::paramsToString()
//{
//    return "RadialDriver params [Kaccel=" + std::to_string(Kaccel) + ", Kspeed=" + std::to_string(Kspeed) 
//            + " posTolerance=" + std::to_string(posTolerance) + " maxSpeed=" + std::to_string(maxSpeed) + "]";
//}
}