#ifndef __AMY_ARM_SPEEDDRIVER_H
#define __AMY_ARM_SPEEDDRIVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/util/ArmModule3.h"
#include "amy/arm/move/SpeedControl.h"

namespace amy
{
// Module for driving a given axis (pan, tilt, radius) at a requested speed.
class SpeedDriver: public ArmModule3
{
public:
    // states of SpeedDriver module
    enum eState
    {
         eSTATE_DONE,     // nothing done
         eSTATE_DRIVE     // moves the arm
    };

private:
    static log4cxx::LoggerPtr logger;
    // logic
    bool bKeepMode;         // indicates the module must work
    float targetSpeed;        // target speed to reach  
    SpeedControl oSpeedControl;      // utility class to drive the joint
    // VS control
    int priority;                   // module's priority in control commands
    JointBus* pVSBus;       // bus connection to VS
    float istTilt;                  // sensed tilt  
    
private:
    
public:
        SpeedDriver();
        //~SpeedDriver();
                
private:
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        // read bus data   
        virtual void senseBus();
        // write action commands to out joint bus
        void writeBus();
};
}
#endif
