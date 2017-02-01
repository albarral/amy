#ifndef __AMY_ARM_AXISKEEPER_H
#define __AMY_ARM_AXISKEEPER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/util/ArmModule3.h"
#include "amy/arm/move/PIDControl.h"
#include "amy/core/MoveState.h"

namespace amy
{
// Module for keeping an axis position. 
// It's made to compensate the arm's tilt when changed due to arm extensions/contractions (radius changes).
class TiltKeeper: public ArmModule3
{
public:
    // states of TiltKeeper module
    enum eState
    {
         eSTATE_DONE,     // nothing done
         eSTATE_DRIVE     // moves the arm
    };

private:
    static log4cxx::LoggerPtr logger;
    // logic
    PIDControl oPIDControl;      // utility class to achieve the target speed (0)
    bool bKeepMode;         // indicates the module must work
    float tiltSpeed;
    float outAccel;
    int priority;                   // module's priority in control commands
    // VS control
    JointBus* pVSBus;       // bus connection to VS
    MoveState oMoveState;   // holds the present move state
    
private:
    
public:
        TiltKeeper();
        //~TiltKeeper();
                
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
