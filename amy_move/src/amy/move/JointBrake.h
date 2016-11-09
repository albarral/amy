#ifndef __AMY_JOINT_BRAKER_H
#define __AMY_JOINT_BRAKER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/utils/Click.h"

namespace amy
{
// This class brakes a joint with a predefined acceleration by reducing the speed till 0.
// The speed output is computed on every go() call. 
class JointBrake
{
private:
    float brakeAccel;          // acceleration of brake movement (degrees/s2)
    float brakeAccel_ms;    // used version of brakeAccel (degres/s)/ms
    float speed;                // commanded speed (degrees/s) 
    // aux
    amy::Click oClick;   

public:
    JointBrake();
    //~JointBrake();

    // control params
    void setBrakeAccel(float value);
    float getBrakeAccel() {return brakeAccel;};                
    // get the output
    float getSpeed() {return speed;};                
        
    // update ellapsed time
    void click();
    // do the control
    void go(float istSpeed);
    
    std::string toString();
};
}
#endif
