/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/arm/move/RadialControl.h"
#include "JointControl.h"

namespace amy
{
RadialControl::RadialControl()
{
    // params default
    workSign = -1; // default downside work plane
}

//RadialControl2::~RadialControl2()
//{
//}

void RadialControl::setArmSize(int lenHumerus, int lenRadius)
{
    oArmMath.setLengths(lenHumerus, lenRadius);
};

void RadialControl::workUp()
{
    workSign = 1;
}

void RadialControl::workDown()
{
    workSign = -1;
}

void RadialControl::newRadialMove(float radius)
{    
    // compute target elbow angle
    float elbowAngle = oArmMath.computeElbowAngle4Radius(radius);    
    // set proper work plane
    elbowAngle = fabs(elbowAngle) * workSign;
    // and prepare for new move
    JointControl::newMove(elbowAngle);
}

std::string RadialControl::toString()
{
    return "RadialControl [target=" + std::to_string(targetAngle) + ", ist=" + std::to_string(prevAngle) 
            + " sollSpeed=" + std::to_string(sollSpeed) + " istSpeed=" + std::to_string(istSpeed) 
            + ", state=" + std::to_string(state) + ", accel=" + std::to_string(outAccel) + "]";
}

std::string RadialControl::paramsToString()
{
    return "RadialControl params [Kaccel=" + std::to_string(Kaccel) + ", Kspeed=" + std::to_string(Kspeed) 
            + " posTolerance=" + std::to_string(posTolerance) + " maxSpeed=" + std::to_string(maxSpeed) + "]";
}
}