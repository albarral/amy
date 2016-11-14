#ifndef __AMY_JOINT_CONTROL2_H
#define __AMY_JOINT_CONTROL2_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/move/JointMover.h"
#include "amy/move/JointBrake.h"
#include "amy/arm/util/JointModule.h"

namespace amy
{
// Lower control module for a joint. Transforms the desired joint acceleration into proper joint positions.
// The movement is limited to the predefined joint's range. A flag is raised when limits are reached.
// It provides auto brake behaviour: on absence of requests it makes the joint brake softly.
class JointControl2 : public JointModule
{
public:    
    // module states
    enum eState
    {
         eSTATE_FREE,             // brakes joint softly
         eSTATE_MOVE            // responds to control inputs
    };
    
private:
    static log4cxx::LoggerPtr logger;
    // logic
    float angle;
    float accel;
    JointMover oJointMover;     // class where movement is computed
    //JointBrake oJointBrake;     // class where autobrake is computed
    //float istSpeed;                // sensed joint speed
    int lowLimit;             // lower joint angle  
    int highLimit;            // higher joint angle  
    bool blimitReached;     // flag raised when the output angle reaches the joint limits
    float brakeAccel;

public:
        JointControl2();
        //~JointControl2();
                
       // module params
       virtual void init(Arm& oArm);
        
private:       
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        
        // read bus data
        void senseBus();
        // write data to bus (speed)
        void writeBus();
        
        bool isLimitReached() {return blimitReached;};
        float limitAngle(float value);

        // shows the present state name
        void showState();        
};
}
#endif
