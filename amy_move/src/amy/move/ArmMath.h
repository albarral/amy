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

   // computes the arm radius given the elbow angle (deg))
   float calcRadius(float angleEL);

   // computes the arm tilt given the vertical shoulder & elbow angles
   //float computeTilt(float angleVS, float angleEL);

   // computes the arm tilt given the arm radius and the vertical shoulder angle
   //float computeTilt2(float radius, float angleVS);

   // computes the arm polar position given the vertical shoulder & elbow angles (deg)
   void calcPolar(float angleVS, float angleEL, float& radius, float& tilt);

   // computes the elbow angle (deg) for a given arm radius
   float calcELAngle(float radius);

   // returns the computed arm's tilt
//   float getArmTilt() {return tilt;};
   // returns the computed arm's radius
//   float getArmRadius() {return radius;};
};
}
#endif
