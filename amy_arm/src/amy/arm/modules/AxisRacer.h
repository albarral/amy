#ifndef __AMY_ARM_AXISRACER_H
#define __AMY_ARM_AXISRACER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/control/PIDControl.h"
#include "amy/arm/util/ArmModule3.h"

namespace amy
{
// (Base) Module for driving a given axis (pan, tilt, radius) at requested speed.
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
   
protected:
    static log4cxx::LoggerPtr logger;
    // control 
    PIDControl oPIDControl;       // PID controller to achieve the target speed    
    float speed1;                     // requested primary speed
    float speed2;                     // requested secondary speed
    bool brequested;                // flag indicating a speed request has arrived
    float targetSpeed;              // final requested axis speed
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

protected:
        // connect module to specific joint
        virtual void setControlledJoint() = 0;
        // read bus data
        virtual void senseBus() = 0;
        // write info (control & sensory) to bus
        virtual void writeBus() = 0;
        
private:
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        // updates target speed
        void updateTargetSpeed();
        // check if controlled joint is blocked (due to reached range limit)
        bool checkBlocked();                                                

        // show module initialization in logs
        virtual void showInitialized();
        // shows the present state name
        void showState();
};
}
#endif
