#ifndef __AMY_ARM_AXISDRIVER3_H
#define __AMY_ARM_AXISDRIVER3_H

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
// Behaviour used to move an arm to a target position along a given axis (pan, tilt or radial).
// The movement is controlled through acceleration commands.
// Movements are done in a single direction. No oscillations are done.  
// For each move, the movement is finished when an arrival point is crossed.
//    
// Base class that needs to be extended (senseBus, writeBus)
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
         eSTATE_ARRIVED,
         eSTATE_DRIVE
    };

protected:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    std::string modName;   // module name
    // params
    float Kaccel;       // acceleration sensitivity
    float Kspeed;     // speed sensitivity
    float driverTolerance;      // position tolerance for driver movements
    float driverSpeed;        // speed used for drive stage (positive value)
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pBus;
    JointBus* pJointBus;   // bus connection to a joint
    MovementControl* pMovementControl;  // shared movement control
    // control 
    int targetPos;          // requested axis position
    // output
    float sollAccel;              // commanded acceleration - JMover
    // measures
    float istPos;            // present axis position
    float istSpeed;         // present arm speed
    float dist;               // present distance to target position
    int blockedTime;     // time that movement has been blocked (due to soll position out of range)    
    // logic
    int moveSign;     // direction of movement (1, -1) 
    float arrivalDist;     // distance at which the movement is considered done
    float targetSpeed;    // desired joint speed (with sign)
    bool bnewMove;    // flag indicating new move requested
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
        // select bus connections to a joint
        virtual void selectBusJoint() = 0;
        // read bus data
        virtual void senseBus() = 0;
        // write action commands to bus
        virtual void writeBus() = 0;
        // computes distance to target
        virtual float computeDistance() = 0;                
        // inform that movement is blocked
        void blockedMove();
        
private:
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        
        // jump to given state
        void jumpTo(int state);
        // updates the target speed
        void setTargetSpeed(float speed);

        // gets a proper speed given the position error
        void controlSpeed();
        // gets a proper acceleration given the target speed
        void controlAccel();
        
        // read params for the movement
        void readParams();
                
        void showMovementData();
        
        // shows the present state name
        void showState();

};
}
#endif
