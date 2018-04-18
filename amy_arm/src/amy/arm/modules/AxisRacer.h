#ifndef __AMY_ARM_AXISRACER_H
#define __AMY_ARM_AXISRACER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/util/ArmModule3.h"
#include "amy/core/bus/AxisBus.h"
#include "amy/core/bus/JointBus.h"
#include "tron/math/PIDControl.h"

namespace amy
{
// Module for driving a given axis (pan, tilt, radius) at a requested speed.
// The module controls a single joint (sends commands to just one).
class AxisRacer: public ArmModule3
{
public:
    // states of ArmRacer module
    enum eState
    {
         eSTATE_DONE,           // nothing done
         eSTATE_NEWMOVE,     // action requested
         eSTATE_DRIVE,           // moves the arm
         eSTATE_BLOCKED,      // movement blocked
    };
   
private:
    static log4cxx::LoggerPtr logger;
    int axis;                       // controlled axis
    // bus
    AxisBus* pAxisBus;       // connection to axis bus
    JointBus* pJointBus;      // connection to specific joint bus
    // control 
    tron::PIDControl oPIDControl;       // PID controller to achieve the target speed    
    bool brequested;                // flag indicating a speed request has arrived
    float targetSpeed;              // requested axis speed
    // sensor
    float axisSpeed;                // measured axis speed
    int jointLimit;                    // value indicating the controlled joint is blocked (due to reached limit)   
    int silentCycles;               // cycles with no requests
    // output
    int priority;                    // module's priority in control commands
    float outAccel;               // commanded joint acceleration     
    
public:
        AxisRacer();
        //~ArmRacer();                
        
        // tunes racer for given axis
        bool tune4Axis(int value);
        
private:
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        // read bus data
        virtual void senseBus();
        // write info (control & sensory) to bus
        virtual void writeBus();

        // connect module to specific joint
        bool setConnections();    
        // check if controlled joint is blocked (due to reached range limit)
        bool checkBlocked();                                                

        // show module initialization in logs
        virtual void showInitialized();
        // shows the present state name
        void showState();
};
}
#endif
