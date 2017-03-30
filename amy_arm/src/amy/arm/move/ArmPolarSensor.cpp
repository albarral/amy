/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/move/ArmPolarSensor.h"

namespace amy
{
ArmPolarSensor::ArmPolarSensor()
{
    istPan = 0.0;         
    istTilt = 0.0;    
    istRadius = 0.0;
}

void ArmPolarSensor::tune(Arm& oArm)
{
    oArmMath.setLengths(oArm.getLenHumerus(), oArm.getLenRadius());
}

void ArmPolarSensor::getTuning(int& lenHumerus, int& lenRadius)
{
    lenHumerus = oArmMath.getLenHumerus();
    lenRadius = oArmMath.getLenRadius();    
}

void ArmPolarSensor::sense(float angleHS, float angleVS, float angleELB)
{
    istPan = angleHS;
    istTilt = oArmMath.computeTilt4JointAngles(angleVS, angleELB);      
    istRadius = oArmMath.computeRadius4ElbowAngle(angleELB);
}
}