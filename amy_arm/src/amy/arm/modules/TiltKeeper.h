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
// Module for keeping a constant tilt position. 
// When it's active it compensates any change to the arm's tilt, except those produced by the tilt driver.
// The module activity is controlled by the CO_KEEP_TILT bus connection.
class TiltKeeper: public ArmModule3
{    
public:
    // states of TiltKeeper module
    enum eState
    {
         eSTATE_DONE,     // nothing done
         eSTATE_WATCH,   // watches for tilt changes
         eSTATE_DRIVE     // moves VS to keep tilt
    };

private:
    static log4cxx::LoggerPtr logger;
    // logic
    PIDControl oPIDControl;      // utility class to achieve the target speed (0)
    bool bActive;                       // indicates the module must work
    float tiltSpeed;                // measured tilt speed
    float outAccel;                 // control VS accel
    int priority;                   // priority of control outputs
    // VS control
    JointBus* pVSBus;            // bus connection to VS
    MoveState oMoveState;     // present move state
    
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
        
        // shows the present state name
        void showState();
};
}
#endif
