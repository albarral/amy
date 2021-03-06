#ifndef __AMY_ARM_JOINTCONTROL_H
#define __AMY_ARM_JOINTCONTROL_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "tron/util/Click.h"

namespace amy
{
// Class used to move a joint to a target position by means of acceleration commands.
// Movements are done in a single direction, without oscillations.
// For each move, the movement is finished when an arrival point is crossed.
// Usage:    
// First initialize the class with sensitivity and tolerance parameters.
// To request a movement, call newMove() with the target angle.
// Then, the drive() function must be called periodically. This internally computes the joint speed and updates the acceleration control.
// Movement is finished when the state is DONE.
class JointControl
{
public:    
    // movement states
    enum eType
    {
         eSTATE_DONE,         // movement finished  
         eSTATE_ARRIVED,     // near to target position (arrived stage)  
         eSTATE_DRIVE          // far from target position (cruise stage)
    };

private:
    const float minResolution = 0.10;   // set minimum resolution (0.1 degrees)

protected:
    // params
    float Kaccel;                   // acceleration sensitivity
    float Kspeed;                 // speed sensitivity
    float posTolerance;      // position tolerance for movement end (fraction)
    float maxSpeed;           // max speed allowed for joint (abs value)
    // request
    float targetAngle;          // requested joint position
    // control 
    float prevAngle;            // previous ist position
    float sollSpeed;    // desired joint speed
    float istSpeed;         // measured joint speed
    int moveSign;           // direction of movement (1, -1) 
    float arrivalDist;     // distance at which the movement is considered done
    int state;                // movement state
    int steps;               // counter of movement steps
    // output
    float outAccel;           // acceleration to control the joint 
    tron::Click oClick;      // clock utility

public:
        JointControl();
        //~JointControl();
                
       void init(float kaccel, float kspeed, float posTolerance, float maxSpeed);

       // new move requested (to new angle)
        virtual void newMove(float angle);
        float getTargetAngle() {return targetAngle;}
        
        // drive the joint with a proper acceleration, the acceleration is returned
        float drive(float istAngle);
        
        int getState() {return state;};
        // check if movement is done
        bool isMovementDone() {return (state==eSTATE_DONE);};

        int getMoveSign() {return moveSign;};
                      
        virtual std::string toString();
        virtual std::string paramsToString();

private:        
        // gets a proper speed given the position error
        void controlSpeed(float dist);
        // gets a proper acceleration given the target speed
        void controlAccel();
        
};
}
#endif
