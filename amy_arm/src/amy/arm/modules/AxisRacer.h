#ifndef __AMY_ARM_AXISRACER_H
#define __AMY_ARM_AXISRACER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/move/PIDControl.h"
#include "amy/arm/util/ArmModule3.h"

namespace amy
{
// Base module for driving a given axis (pan, tilt, radius) at a requested speed.
// A single joint is controlled (by acceleration). 
class AxisRacer: public ArmModule3
{
public:
    // states of AxisRacer module
    enum eState
    {
         eSTATE_IDLE,           // nothing done
         eSTATE_GO,              // action requested
         eSTATE_DRIVE,           // moves the arm
         eSTATE_BLOCKED,      // movement blocked
    };

protected:
    static log4cxx::LoggerPtr logger;
    // control 
    PIDControl oPIDControl;      // utility class to achieve the target speed    
    float targetSpeed;         // requested axis speed
    float istSpeed;               // measured axis speed
    int jointLimit;                 // value indicating the controlled joint is blocked (due to a reached joint limit)   
    // output
    float outAccel;              // commanded joint acceleration 
    int priority;                   // module's priority in control commands

private:
    
public:
        AxisRacer();
        //~AxisRacer();                
                      
protected:
        // read bus data
        virtual void senseBus() = 0;
        // write info (control & sensory) to bus
        virtual void writeBus() = 0;
        // connect module output to specific joint
        virtual void connectOutput() = 0;
        
private:
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        // check if controlled joint is blocked (due to reached range limit)
        bool checkBlocked();                                                
        // shows the present state name
        void showState();
};
}
#endif
