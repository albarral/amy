#ifndef __AMY_MOVE_SPEEDCONTROL_H
#define __AMY_MOVE_SPEEDCONTROL_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/arm/move/PIDControl.h"

namespace amy
{
// Utility class to achieve a requested axis speed (pan, tilt, radius)
class SpeedControl
{
private:
    // control 
    PIDControl oPIDControl;         // PID controller to achieve the target speed    
    float targetSpeed;                // requested axis speed
    // output
    bool blocked;                       // indicates axis move is blocked due to a joint reached limit
    float outAccel;                     // commanded joint acceleration 
        
public:
        SpeedControl();
        //~SpeedControl();                
        
        // init PID controller
        void init(float Kp, float Ki, float Kd);
        // set controller target
        void setTargetSpeed(float value) {targetSpeed = value;};
        // restart controller (use to reset PID history)       
        void restart();
        // compute movement and check move is blocked due to a joint reached limit
        float move(float istSpeed, int jointLimit);
        // check if movement is blocked
        bool isBlocked() {return blocked;};             
        float getOutAccel() {return outAccel;};
        
        // return description 
         std::string toString();
};
}
#endif
