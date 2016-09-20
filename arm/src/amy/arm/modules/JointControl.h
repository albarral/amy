#ifndef __AMY_JOINT_CONTROL_H
#define __AMY_JOINT_CONTROL_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/utils/module2.h"
#include "amy/utils/Click.h"
#include "amy/arm/bus/JointBus.h"
#include "amy/arm/data/Joint.h"

namespace amy
{
// Last module in the arm's control chain. It transforms the desired joint speed into proper joint positions.
class JointControl : public Module2
{
public:
    // states of JointControl module
    enum eState
    {
         eSTATE_GO
    };

private:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    // params
    std::string modName;   // module name
    Joint* mJoint;        // controlled joint  
    // bus
    bool bconnected;        // connected to bus
    JointBus* pJointBus;    // the bus connections corresponding to a given joint
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
       void init (std::string jointName, Joint& oJoint);       
       bool isEnabled() {return benabled;};

       // bus connection               
       void connect(JointBus& oConnectionsJoint);              
       bool isConnected() {return bconnected;};

        Joint* getJoint() {return mJoint;};
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
