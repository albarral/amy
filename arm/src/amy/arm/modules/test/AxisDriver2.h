#ifndef __AMY_ARM_AXISDRIVER2_H
#define __AMY_ARM_AXISDRIVER2_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/bus/MovementControl.h"
#include "amy/utils/module3.h"
#include "amy/utils/Record.h"   // tmp for analysis

namespace amy
{
// Behaviour used to move an arm to a target position along a single polar axis (pan, tilt or radial).
// The movement is controlled through acceleration commands.
// Movements are performed in a single direction. No oscillations are allowed. 
//
// Base class that needs to be extended (senseBus, writeBus)
// - States: 
// DRIVE:           high constant speed - when far from target   
// APPROACH:    low variable speed  - when near to target  
// ARRIVED:        null speed - when at target (tolerance)
// - Outputs:
// acceleration commands
class AxisDriver2: public Module3
{
public:
    // states of AxisDriver2 module
    enum eType
    {
         eSTATE_DONE,
         eSTATE_ARRIVED,
         eSTATE_APPROACH,
         eSTATE_DRIVE
    };

protected:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    std::string modName;   // module name
    // params
    float tolPos;       // tolerance in distance control (fraction)
    float tolSpeed;    // tolerance in speed control (fraction))
    int resolution;   // minimum distance resolution
    float Kaccel;       // acceleration sensitivity
    float Kspeed;     // speed sensitivity
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pBus;
    JointBus* pJointBus;   // bus connection to a joint
    MovementControl* pMovementControl;  // shared movement control
    // control 
    int targetPos;          // requested axis position
    float time4move;    // requested time for move
    // output
    int accel;              // commanded acceleration - JMover
    // measures
    float istPos;            // real axis position
    float dist;                 // position error
    float sollSpeed;         // real arm speed
    int blockedTime;     // time that movement has been blocked (ie for limit reasons)    
    // logic
    float posTol;            // tolerance allowed around final position
    int movementDir;     // direction of movement (1, -1) kept constant  
    float targetSpeed;    // desired arm speed
    float speedTol;         // tolerance allowed around target speed 
    int maxAccel;          // central max acceleration
    float dBrake;           // distance needed to brake at maximum acceleration
    bool bnewRequest;    // flag indicating new move requested
    // aux
    Record oRecord; // record to store the speed evolution in movement  (for analysis purpose)

public:
        AxisDriver2();
        //~AxisDriver2();
                
       // module params
       void init(float tolPos, float tolSpeed, int vApproach, MovementControl& oMovementControl);
       bool isEnabled() {return benabled;};

       // bus connection 
       void connect(ArmBus& oBus);
       bool isConnected() {return bconnected;};

       // record output for analysis
       Record& getRecord() {return oRecord;};
                      
protected:               
        // select bus connections to a joint
        virtual void selectBusJoint() = 0;
        // read bus data
        virtual void senseBus() = 0;
        // write action commands to bus
        virtual void writeBus() = 0;
                
        // movement is blocked
        void blockedMove();
        // shows the present state name
        void showState();
        
private:
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            

        // jump to given state
        void jumpTo(int state);
        // updates the target speed
        void updateTargetSpeed(float speed);
        // computes the position tolerance
        void updatePosTolerance(float dist);

        // gets a proper speed given the position error
        void controlSpeed();
        // gets a proper acceleration given the target speed
        void controlAccel();
        
        void showMovementData();
};
}
#endif
