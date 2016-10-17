/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/math/ArmTrigonometry.h"

#define PI 3.1416
#define KPI_DIV_180 0.0174
#define K180_DIV_PI 57.2958


namespace amy
{
// computes all the move steps in a movement
ArmTrigonometry::ArmTrigonometry()
{
    len1 = 20;      // 20 cm default 
    len2 = 20;
    tilt = 0;
    radius = 0;
}

void ArmTrigonometry::setLengths(int len1, int len2)
{
    if (len1>0)
        this->len1 = len1;
    if (len2>0)
        this->len2 = len2;
}

void ArmTrigonometry::compute(float angleVS, float angleELB)
{
    float radians1 = angleVS * KPI_DIV_180;
    float radians2 = angleELB * KPI_DIV_180;
    // get base
    float b = len1 * cos(radians1) + len2 * cos(radians2);
    // get height
    float h = len1 * sin(radians1) + len2 * sin(radians2);
    
    // beta = arctg(h/b)
    tilt = atan2(h, b) * K180_DIV_PI;
    
    // radius = sqrt(h² + b²)
    radius = sqrt(h*h + b*b);
};


}
