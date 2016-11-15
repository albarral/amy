#ifndef __AMY_ARM_AXISDRIVER3_H
#define __AMY_ARM_AXISDRIVER3_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/move/JointDriver.h"
#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/bus/MovementControl.h"
#include "amy/utils/module3.h"
#include "amy/utils/Record.h"   // tmp for analysis

namespace amy
{
// Behaviour used to move an arm to a target position along a given axis (pan, tilt or radial).
// The movement is controlled through acceleration commands.
// Movements are done in a single direction. No oscillations are done.  
// For each move, the movement is finished when an arrival point is crossed.
//    
// Base class that needs to be extended 
// - States: 
// DRIVE:           adaptive speed (max limited) - when far from target   
// ARRIVED:        null speed - when at target (tolerance)
// - Outputs:
// acceleration commands
class AxisDriver3: public Module3
{
public:
    // states of AxisDriver3 module
    enum eType
    {
         eSTATE_DONE,
         eSTATE_DRIVE
    };

protected:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pBus;
    MovementControl* pMovementControl;  // shared movement control
    // request
    float targetPos;          // requested joint position
    // control 
    float istPos;                // measured joint position
    JointDriver oJointDriver;      // utility class used to drive the joint
    int blockedTime;     // time that movement has been blocked (due to soll position out of range)    
    bool bnewMove;    // flag indicating new move requested
    int limitReached;     // value indicating the movement is blocked (due to joint limits reached)    
    // output
    float sollAccel;              // commanded acceleration 
    // aux
    Record oRecord; // record to store the speed evolution in movement  (for analysis purpose)

public:
        AxisDriver3();
        //~AxisDriver3();
                
       // module params
       void init(MovementControl& oMovementControl);
       bool isEnabled() {return benabled;};

       // bus connection 
       void connect(ArmBus& oBus);
       bool isConnected() {return bconnected;};

       // record output for analysis
       Record& getRecord() {return oRecord;};
                      
protected:               
        // select bus connections to affected joints
        virtual void selectBusJoints() = 0;
        // read bus data
        virtual void senseBus() = 0;
        // write action commands to bus
        virtual void writeBus() = 0;
        
private:
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
                
        // prepare for new movement
        void newMove();
        // movement finished
        void done();
        // check if movement is blocked
        bool isMovementBlocked();
                
        void showMovementData();
        
        // shows the present state name
        void showState();

};
}
#endif
