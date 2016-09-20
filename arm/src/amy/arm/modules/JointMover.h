#ifndef __AMY_JOINT_MOVER_H
#define __AMY_JOINT_MOVER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/utils/module2.h"
#include "amy/utils/Click.h"
#include "amy/arm/config/ParamsJointMover.h"
#include "amy/arm/bus/JointBus.h"

namespace amy
{
// Version 3    
// Module designed to perform dynamic & soft movements with a joint, providing an auto brake behaviour.
// It assures speed continuity by limiting the joint's acceleration.
// On control requests (push, push_back and keep) it accelerates or keeps the speed of the joint.
// On absence of request, it brakes the joint (limited deceleration) till speed is 0.    
// States: 
// AUTOBRAKE (default): if speed != 0 -> |speed|--
// KEEP: speed =
// ACCEL: speed ++ or speed --    
class JointMover : public Module2
{
public:
    // input commands
    enum eCommands
    {
        eMOV_STOP,
        eMOV_KEEP,
        eMOV_PUSH_FRONT,
        eMOV_PUSH_BACK,
    };

    // states of JointMover module
    enum eState
    {
         eSTATE_BRAKE,              // brakes joint softly
         eSTATE_KEEP,               // keeps present joint speed 
         eSTATE_ACCEL             // alters joint speed 
    };

private:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    // params
    std::string modName;   // module name
    int accel;                  // acceleration/deacceleration of joint movements (degrees/s2)
    float accel_ms;             // used version of accel (degres/s)/ms
    int brakeAccel;          // deacceleration of brake movements (degrees/s2)
    float brakeAccel_ms;     // used version of brakeAccel (degres/s)/ms
    // bus
    bool bconnected;        // connected to bus
    JointBus* pJointBus;    // the bus connections corresponding to a given joint
    // control
    int targetDirection;     // direction of desired movement (positive or negative)
    // logic
    float sollSpeed;      // final speed commanded to output (degrees/s) (is always continuous)
    amy::Click oClick;   
    // aux
    float lastOutput;

public:
        JointMover();
        //~JointMover();
                
       // module params
       void init (std::string jointName, ParamsJointMover& oParamsJointMover);       
       bool isEnabled() {return benabled;};

       // bus connection 
       void connect(JointBus& oConnectionsJoint);
       bool isConnected() {return bconnected;};
       // params
        void setAccel(int value) {accel = value;};
        void setBrakeAccel(int value) {brakeAccel = value;};
        int getAccel() {return accel;};
        int getBrakeAccel() {return brakeAccel;};                
                
private:       
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        
        // read bus data
        void senseBus();
        // write data to bus (speed)
        void writeBus();

        // process action requests (from bus)
        void processRequest(int value);
        
        // changes the output speed in the proper direction
        void doAccelerate();
        // softly reduces speed to 0
        void doBrake();
                
        // shows the present state name
        void showState();
};
}
#endif
