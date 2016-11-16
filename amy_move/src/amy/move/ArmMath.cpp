/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/move/ArmMath.h"

#define PI 3.1416
#define KPI_DIV_180 0.0174
#define K180_DIV_PI 57.2958


namespace amy
{
// computes all the move steps in a movement
ArmMath::ArmMath()
{
    setLengths(20, 20);    // 20 cm default 
}

// update lengths and collateral values
void ArmMath::setLengths(int lenHum, int lenRad)
{
    if (lenHum>0)
        lenHumerus = lenHum;
    if (lenRad>0)
        lenRadius = lenRad;
    
    // compute collateral values
    sumSquares = lenHumerus*lenHumerus + lenRadius*lenRadius;
    doubleProduct = 2*lenHumerus*lenRadius;
    maxRadius = lenHumerus + lenRadius;
    minRadius = lenHumerus - lenRadius;
    if (minRadius < 0.0)
        minRadius = 0.0;
}

float ArmMath::calcRadius(float angleEL)
{
    float radiansEL = angleEL * KPI_DIV_180;
    
    // radius computation
    return (sqrt(sumSquares + doubleProduct*cos(radiansEL)));
}

void ArmMath::calcPolar(float angleVS, float angleELB, float& radius, float& tilt) 
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

float ArmMath::calcELAngle(float radius)
{
    // to avoid limit radius to the valid range
    if (radius > maxRadius)
        radius = maxRadius;
    else if (radius < minRadius)
        radius = minRadius;
    
    float cosinus = (radius*radius - sumSquares)/doubleProduct;
    
    // angle computation
    float radiansEL = acos((radius*radius - sumSquares)/doubleProduct);    
    
    return radiansEL * K180_DIV_PI;
}

}
