#ifndef __AMY_MATH_ARMTRIGONOMETRY_H
#define __AMY_MATH_ARMTRIGONOMETRY_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace amy
{
// Class used to tranform from joint angles to arm angle and radius.
// It does computations using a 2 segment arm model. 
// It delivers the position (tilt & radius) of the wrist.
    
class ArmTrigonometry
{
private:
    int len1;   // length of 1st segment: shoulder-elbow (cm)
    int len2;   // length of 2nd segment: elbow-wrist (cm)
    float tilt;         // arm tilt at wrist (degrees))
    float radius;   // arm radius at wrist (cm)
    
public:  
    ArmTrigonometry();
    //~ArmTrigonometry();

    void setLengths(int len1, int len2);
    
   // computes the wrist position at given vertical shoulder & elbow angles
   void compute(float angleVS, float angleELB);

   // returns the computed arm's tilt
   float getArmTilt() {return tilt;};
   // returns the computed arm's radius
   float getArmRadius() {return radius;};
};
}
#endif
