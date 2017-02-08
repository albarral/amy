#ifndef __AMY_MOVE_ARMPOLARSENSOR_H
#define __AMY_MOVE_ARMPOLARSENSOR_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/move/ArmMath.h"
#include "amy/core/robot/Arm.h"

namespace amy
{
// Class used to compute an arm's polar positions (pan, tilt and radius).
// It must be tuned to the arm before using it.
class ArmPolarSensor
{
private:
    float istPan;           // computed pan value (degrees)
    float istTilt;           // computed tilt value (degrees)
    float istRadius;      // computed radius value (cm)
    ArmMath oArmMath;   // utility class for arm computations

public:
        ArmPolarSensor();
        //~ArmPolarSensor();
                
       // tune sensor to arm sizes
       void tune(Arm& oArm);
       void getTuning(int& lenHumerus, int& lenRadius);               

       // compute polar positions
        void sense(float angleHS, float angleVS, float angleELB);

        float getPanAngle() {return istPan;}
        float getTiltAngle() {return istTilt;}
        float getRadius() {return istRadius;}
};
}
#endif
