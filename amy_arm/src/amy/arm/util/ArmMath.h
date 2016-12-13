#ifndef __AMY_ARM_ARMMATH_H
#define __AMY_ARM_ARMMATH_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace amy
{
// Class used to do arm related computations 
    
class ArmMath
{
public:    
   // computes distance needed to brake completely from given speed using uniform acceleration (understood as deacceleration)
   static float computeBrakeDistance(float speed, float accel);
   
   // computes the position resolution of a movement given its speed and the measurement frequency
   static float getMovementResolution(float speed, float freq);
};
}
#endif
