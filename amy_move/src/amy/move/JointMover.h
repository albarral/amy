#ifndef __AMY_MOVE_JOINTMOVER_H
#define __AMY_MOVE_JOINTMOVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/utils/Click.h"

namespace amy
{
// This class transforms joint acceleration commands into the corresponding joint movement (position and speed).
// The move() function must be called periodically to get the updated joint position.
// A brake mode is also available, which reduces the speed until 0 is reached.
// The brake mode works by periodically calling the brake() function instead of move().
// The elapsed time between calls is measured and used for the movement computation.
class JointMover
{
private:
    float accel;               // commanded acceleration (degrees/s2)
    float finalSpeed;       // final speed in last control period (degrees/s) 
    float speed;             // average speed in last control period, used for the position update (degrees/s) 
    float angle;              // resulting joint angle (degrees)
    amy::Click oClick;      // clock utility

public:
    JointMover();
    //~JointMover();

    // control inputs
    float getAccel() {return accel;};                
    float getSpeed() {return speed;};                
    float getAngle() {return angle;};                

    // move the joint with the given acceleration, the joint angle is returned
    float move(float acceleration, float istAngle);
    // brake the joint with the given deceleration, the joint angle is returned
    float brake(float deceleration, float istAngle);
    // do nothing
    void iddle();
        
    std::string toString();
       
private:
};
}
#endif
