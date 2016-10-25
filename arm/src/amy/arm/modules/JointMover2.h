#ifndef __AMY_JOINT_MOVER2_H
#define __AMY_JOINT_MOVER2_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/utils/module2.h"
#include "amy/utils/Click.h"
#include "amy/arm/bus/JointBus.h"

namespace amy
{
// Version 4    
// This module responds to acceleration commands by transforming them to appropriate joint speed ones.
// It provides auto brake behaviour: on absence of requests it makes the joint brake softly till speed is 0.
// States: 
// BRAKE: if speed != 0 -> |speed|--
// ACCEL: speed ++ or speed --    
class JointMover2 : public Module2
{
public:
    // states of JointMover2 module
    enum eState
    {
         eSTATE_BRAKE,             // brakes joint softly
         eSTATE_ACCEL             // alters joint speed 
    };

private:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    // params
    std::string modName;   // module name
    int brakeAccel;          // deacceleration of brake movements (degrees/s2)
    float brakeAccel_ms;     // used version of brakeAccel (degres/s)/ms
    // bus
    bool bconnected;        // connected to bus
    JointBus* pJointBus;    // the bus connections corresponding to a given joint
    // control
    int accel;                  // acceleration/deacceleration of joint movements (degrees/s2)
    float accel_ms;         // used version of accel (degres/s)/ms
    // output
    float sollSpeed;      // final speed commanded to output (degrees/s) 
    // aux
    amy::Click oClick;   
    float lastOutput;

public:
        JointMover2();
        //~JointMover2();
                
       // module params
       void init (std::string jointName, int brakeAccel);       
       bool isEnabled() {return benabled;};

       // bus connection 
       void connect(JointBus& oConnectionsJoint);
       bool isConnected() {return bconnected;};
       // params
        void setBrakeAccel(int value) {brakeAccel = value;};
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

        void setAccel(int value) {accel = value;};
        int getAccel() {return accel;};

        // changes the output speed in the proper direction
        void doAccelerate();
        // softly reduces speed to 0
        void autoBrake();
                
        // shows the present state name
        void showState();
};
}
#endif
