#ifndef __AMY_MOVE_SPEEDCONTROL_H
#define __AMY_MOVE_SPEEDCONTROL_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/utils/Click.h"

namespace amy
{
// Class used to move a joint at a target speed by means of acceleration commands.
// Usage:    
// First initialize the class with sensitivity and tolerance parameters.
// To request a movement, call newMove() with the target speed.
// Then, the drive() function must be called periodically. 
class SpeedControl
{
private:
    // params
    float Kaccel;                   // acceleration sensitivity
    //float speedTolerance;      // speed tolerance for movement end (fraction)
    // logic
    float sollSpeed;          // requested joint speed
    float istSpeed;          // measured joint speed
    float prevAngle;         // previous ist position
    bool bjustStarted;     // flag indicating first iteration (unable to measure speed)
    amy::Click oClick;      // clock utility
    // output
    float outAccel;           // acceleration to control the joint 

public:
        SpeedControl();
        //~SpeedControl();
                
       void init(float kaccel, float speedTolerance);

       // new move requested (at target speed)
        void newMove(float speed);
        float getSollSpeed() {return sollSpeed;}
        
        // drive the joint with a proper acceleration, the acceleration is returned
        float drive(float istAngle);
                              
        virtual std::string toString();

private:        
        // gets a proper acceleration given the target speed
        void controlAccel();
        
};
}
#endif
