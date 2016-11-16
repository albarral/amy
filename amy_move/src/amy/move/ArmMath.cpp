/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/move/ArmTrigonometry.h"

#define PI 3.1416
#define KPI_DIV_180 0.0174
#define K180_DIV_PI 57.2958


namespace amy
{
// computes all the move steps in a movement
ArmTrigonometry::ArmTrigonometry()
{
    lenHumerus = 20;      // 20 cm default 
    lenRadius = 20;
    tilt = 0;
    radius = 0;
}

void ArmTrigonometry::setLengths(int lenHum, int lenRad)
{
    if (lenHum>0)
        this->lenHumerus = lenHum;
    if (lenRad>0)
        this->lenRadius = lenRad;
}

void ArmTrigonometry::computeWristPosition(float angleVS, float angleELB)
{
    float radians1 = angleVS * KPI_DIV_180;
    float radians2 = (angleVS + angleELB) * KPI_DIV_180;
    // get base
    float b = lenHumerus * cos(radians1) + lenRadius * cos(radians2);
    // get height
    float h = lenHumerus * sin(radians1) + lenRadius * sin(radians2);
    
    // beta = arctg(h/b)
    tilt = atan2(h, b) * K180_DIV_PI;
    
    // radius = sqrt(h² + b²)
    radius = sqrt(h*h + b*b);
};


}
