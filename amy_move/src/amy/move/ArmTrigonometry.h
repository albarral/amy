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
    int lenHumerus;   // length of Humerus segment: shoulder-elbow (cm)
    int lenRadius;      // length of Radius segment: elbow-wrist (cm)
    float tilt;         // arm tilt at wrist (degrees))
    float radius;   // arm radius at wrist (cm)
    
public:  
    ArmTrigonometry();
    //~ArmTrigonometry();

    void setLengths(int lenHum, int lenRad);
    
   // computes the wrist position at given vertical shoulder & elbow angles
   void computeWristPosition(float angleVS, float angleELB);

   // returns the computed arm's tilt
   float getArmTilt() {return tilt;};
   // returns the computed arm's radius
   float getArmRadius() {return radius;};
};
}
#endif
