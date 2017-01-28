#ifndef __AMY_MOVE_ARMMATH_H
#define __AMY_MOVE_ARMMATH_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace amy
{
// Class used to perform mathematic computations on a 2 segments arm.
// Converts from joint angles to polar coordinates (tilt & radius) and viceversa.
// The class must be initialized with the segments lengths.    
class ArmMath
{
private:
    int lenHumerus;   // length of Humerus segment: shoulder-elbow (cm)
    int lenRadius;      // length of Radius segment: elbow-wrist (cm)
    // collateral values
    float sumSquares;   // square(Humerus length) + square(Radius length)
    float doubleProduct;   // 2 * Humerus length * Radius length
    float maxRadius;
    float minRadius;
    
public:  
    ArmMath();
    //~ArmTrigonometry();

    // store segment lengths (cm))
    void setLengths(int lenHum, int lenRad);

   // computes the arm radius (cm) for the given the elbow angle (deg)
   float convJoints2ArmRadius(float angleEL);

   // computes the arm tilt position given the vertical shoulder & elbow angles (deg)
   float convJoints2ArmTilt(float angleVS, float angleEL);

   // computes the elbow angle (deg) for a given arm radius (cm)
   float convArmRadius2Elbow(float radius);
};
}
#endif