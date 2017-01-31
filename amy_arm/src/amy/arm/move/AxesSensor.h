#ifndef __AMY_MOVE_AXESSENSOR_H
#define __AMY_MOVE_AXESSENSOR_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/move/ArmMath.h"
#include "amy/core/robot/Arm.h"
//#include "amy/utils/Click.h"

namespace amy
{
// Class used to compute the axes positions and speeds of an arm (pan, tilt and radius).
// It must be tuned to the arm before using it.
class AxesSensor
{
private:
    float istPan;           // computed pan value (degrees)
    float istTilt;           // computed tilt value (degrees)
    float istRadius;      // computed radius value (cm)
    //amy::Click oClick;       // utility class for time measurements
    ArmMath oArmMath;   // utility class for arm computations

public:
        AxesSensor();
        //~AxesSensor();
                
       // tune sensor to arm sizes
       void tune(Arm& oArm);
       void getTuning(int& lenHumerus, int& lenRadius);               

       // computes axes positions
        void computeAxes(float angleHS, float angleVS, float angleELB);

        float getPanAngle() {return istPan;}
        float getTiltAngle() {return istTilt;}
        float getRadius() {return istRadius;}
};
}
#endif
