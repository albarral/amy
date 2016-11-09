#ifndef __AMY_JOINT_CONTROL_H
#define __AMY_JOINT_CONTROL_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/util/JointModule.h"
#include "amy/utils/Click.h"
#include "amy/robot/Joint.h"

namespace amy
{
// Last module in the arm's control chain. It transforms the desired joint speed into proper joint positions.
class JointControl : public JointModule
{
public:
    // states of JointControl module
    enum eState
    {
         eSTATE_GO
    };

private:
    static log4cxx::LoggerPtr logger;
    // params
    Joint* pJoint;        // controlled joint  
    // logic
    float sollSpeed;        // speed requested by higher modules (deg/s)
    float sollSpeed_ms;  // speed requested by higher modules (deg/ms))
    float sollAngle;        // angle requested by this module (float to grant continuity)
    float prevSollAngle;       
    amy::Click oClick;   
    int limitReached;    // commanded angle out of joint's range  

public:
        JointControl();
        //~JointControl();
                
       // module params
        virtual void init(Arm& oArm);

        Joint* getJoint() {return pJoint;};
        float getAngle() {return sollAngle;};
        
private:       
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        
        // read bus data
        void senseBus();
        // write data to bus (speed)
        void writeBus();
        
        // translate commanded speed into next joint angle
        void doSpeed2Angle();
};
}
#endif
