#ifndef __AMY_MOVE_JOINTACCELERATOR_H
#define __AMY_MOVE_JOINTACCELERATOR_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/math/Click.h"

namespace amy
{
// This class transforms joint acceleration commands into the corresponding joint movement (position and speed).
// The move() function must be called periodically to get the updated joint position.
// A brake mode is also available, which reduces the speed until 0 is reached.
// The brake mode works by periodically calling the brake() function instead of move().
// The elapsed time between calls is measured and used for the movement computation.
class JointAccelerator
{
private:
    float accel;                // average speed in last control period, used for the position update (degrees/s) 
    float speed;             // average speed in last control period, used for the position update (degrees/s) 
    float angle;              // obtained joint angle (degrees)
    float prevAngle;        // last measured joint angle (degrees)
    float time;                //elapsed time (secs)
    amy::Click oClick;      // clock utility

public:
    JointAccelerator();
    //~JointMove();

    // control inputs
    float getSpeed() {return speed;};                
    float getAngle() {return angle;};                

    // move the joint with the given acceleration, the joint angle is returned
    float move(float istAngle, float acceleration);
    // brake the joint with the given deceleration, the joint angle is returned
    float brake(float istAngle, float deceleration);
    // just update the accelertor with the measured joint angle
    void touch(float istAngle);
    // reset
    void reset();
        
    std::string toString();
       
private:
};
}
#endif
