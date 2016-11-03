#ifndef __AMY_JOINT_MOVER_H
#define __AMY_JOINT_MOVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

//#include <string>

#include "amy/utils/Click.h"

namespace amy
{
// This class controls the position and speed of a joint in response to acceleration commands.
// The movement is limited to the predefined joint's range. A flag is raised when limits are reached.
// The angle is computed on every go() call. 
// If needed, control can be done through speed or position commands (in these cases, previous acceleration or speeds are ignored)
class JointMover
{
private:
    float accel;                // required acceleration/deacceleration (degrees/s2)
    float accel_ms;         // used accel ((degres/s)/ms)
    float speed;             // resulting joint speed (degrees/s) 
    float speed_ms;       // used speed (degrees/ms) 
    float angle;              // resulting joint angle (degrees)
    int lowLimit;
    int highLimit;
    bool blimitReached;
    // aux
    amy::Click oClick;   

public:
    JointMover();
    //~JointMover();

    void init (int lowPos, int highPos);       

    void setAccel(float value);
    float getAccel() {return accel;};                

    void setSpeed(float value);
    float getSpeed() {return speed;};                

    void setAngle(float value);
    float getAngle() {return angle;};                

    void go();
       
private:
    void limitAngle(float value);
};
}
#endif
