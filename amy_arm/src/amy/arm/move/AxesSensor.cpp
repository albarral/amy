/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/arm/move/AxesSensor.h"

namespace amy
{
AxesSensor::AxesSensor()
{
    istPan = 0.0;         
    istTilt = 0.0;    
    istRadius = 0.0;
}

void AxesSensor::tune(Arm& oArm)
{
    oArmMath.setLengths(oArm.getLenHumerus(), oArm.getLenRadius());
}

void AxesSensor::getTuning(int& lenHumerus, int& lenRadius)
{
    lenHumerus = oArmMath.getLenHumerus();
    lenRadius = oArmMath.getLenRadius();    
}

void AxesSensor::computeAxes(float angleHS, float angleVS, float angleELB)
{
    istPan = angleHS;
    istTilt = oArmMath.computeTilt4JointAngles(angleVS, angleELB);      
    istRadius = oArmMath.computeRadius4ElbowAngle(angleELB);
}
}