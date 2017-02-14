#ifndef __AMY_ARM_ARMRACER_H
#define __AMY_ARM_ARMRACER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/move/SpeedControl.h"
#include "amy/arm/util/ArmModule3.h"

namespace amy
{
// Module for driving a the arm's axes (pan, tilt, radius) at requested speeds.
class ArmRacer: public ArmModule3
{
public:
    // states of ArmRacer module
    enum eState
    {
         eSTATE_IDLE,           // nothing done
         eSTATE_GO,              // action requested
         eSTATE_DRIVE,           // moves the arm
         eSTATE_BLOCKED,      // movement blocked
    };

private:
    static log4cxx::LoggerPtr logger;
    // control 
    SpeedControl oSpeedControlPan;    // PID controller to achieve the target pan speed    
    SpeedControl oSpeedControlTilt;    // PID controller to achieve the target tilt speed    
    SpeedControl oSpeedControlRad;    // PID controller to achieve the target radial speed    
    float panSpeed;            // measured pan speed
    float tiltSpeed;             // measured tilt speed
    float radialSpeed;         // measured radial speed
    int limitHS;                      // value indicating the pan is blocked (due to reached HS limit)   
    int limitVS;                      // value indicating the tilt is blocked (due to reached VS limit)   
    int limitELB;                     // value indicating the radius is blocked (due to reached ELB limit)   
    // output
    int priority;                   // module's priority in control commands
    float accelHS;                // commanded HS acceleration 
    float accelVS;                // commanded VS acceleration 
    float accelELB;              // commanded ELB acceleration 
    JointBus* pHSBus;         // bus connection to HS
    JointBus* pVSBus;         // bus connection to VS
    JointBus* pELBus;          // bus connection to EL
    
    
public:
        ArmRacer();
        //~ArmRacer();                
                              
private:
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        // read bus data
        virtual void senseBus();
        // write info (control & sensory) to bus
        virtual void writeBus();
        // show module initialization in logs
        virtual void showInitialized();

        // check if controlled joint are blocked (due to reached range limit)
        bool checkBlocked();                                                
        // shows the present state name
        void showState();
};
}
#endif
