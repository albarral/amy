#ifndef __AMY_JOINT_DRIVER_H
#define __AMY_JOINT_DRIVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/move/JointDrive.h"
#include "amy/arm/util/JointModule.h"

namespace amy
{
// Lower control module for a joint. Transforms the desired joint acceleration into proper joint positions.
// The movement is limited to the predefined joint's range. A flag is raised when limits are reached.
// It provides auto brake behaviour: on absence of requests it makes the joint brake softly.
class JointDriver : public JointModule
{
public:    
    // module states
    enum eState
    {
         eSTATE_DONE,            // nothing done
         eSTATE_MOVE,            // moves joint at given acceleration
         eSTATE_BRAKE             // brakes joint softly
    };
    
private:
    static log4cxx::LoggerPtr logger;
    // logic
    bool baccel;         // indicates no input received
    JointDrive oJointDrive;     // utility class used to compute the joint movement 
    float angle;
    float accel;
    int lowLimit;             // lower joint angle  
    int highLimit;            // higher joint angle  
    int limitReached;     // value indicating that the output angle has reached the joint limits
    float brakeAccel;

public:
        JointDriver();
        //~JointDriver();
                
       // module params
       virtual void init(Arm& oArm, ArmConfig& oArmConfig);
        
private:       
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        
        // read bus data
        void senseBus();
        // write data to bus (speed)
        void writeBus();
        
        float limitAngle(float value);

        // shows the present state name
        void showState();        
};
}
#endif
