#ifndef __AMY_ARM_AXISDRIVER_H
#define __AMY_ARM_AXISDRIVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/bus/MovementControl.h"
#include "amy/utils/module3.h"

namespace amy
{
// Behaviour used to move an arm to a target position in a single direction (pan, tilt or radial)
// It's a base class that needs to be extended (senseBus & writeBus to be implemented)
// Movements done in 3 stages: 
// DRIVE:           high speed - far from target   (d > dbrake)
// APPROACH:    low speed  - near to target     (d < dbrake)
// ARRIVED:        brake - target reached           (d < tolerance)  
// - Outputs:
// actions and acceleration for JointMover modules
class AxisDriver: public Module3
{
public:
    // states of AxisDriver module
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
    int dTol;     // arrived threshold distance
    float vTol;    // tolerance in speed control
    float Kaccel;       // acceleration sensitivity
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pBus;
    JointBus* pJointBus;   // bus connection to a joint
    MovementControl* pMovementControl;  // shared movement control
    // control input
    int targetPos;          // requested axis position
    // control output
    int accel;              // commanded acceleration - JMover
    int outAction;          // commanded action - JMover
    // logic
    bool bnewRequest;    // flag indicating new move requested
    int vDrive;             // drive speed 
    int vApproach;     // approach speed
    int accel0;      // default acceleration
    float targetSpeed;    // desired arm speed
    float sollSpeed;         // real arm speed
    float istPos;            // real axis position
    int blockedTime;     // time that movement has been blocked (ie for limit reasons)
    // tolerances
    int vDriveTol;         // tolerance over drive speed (deg/s)
    int vApproachTol;     // tolerance over approach speed (deg/s)            
    float speedTol;         // tolerance over target speed 

public:
        AxisDriver();
        //~AxisDriver();
                
       // module params
       void init(int dTol, int vApproach, float speedTolerance, MovementControl& oMovementControl);
       bool isEnabled() {return benabled;};

       // bus connection 
       void connect(ArmBus& oBus);
       bool isConnected() {return bconnected;};
       
               
protected:       
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        
        // select bus connections to a joint
        virtual void selectBusJoint() = 0;
        // read bus data
        virtual void senseBus() = 0;
        // write action commands to bus
        virtual void writeBus() = 0;
        
        // prepares for new move
        void newMove(float dist);
        // move joint to target position at proper speed
        //void doDrive(float dist, float absDist);
        // stop joint movement
        void doArrived();
        
        // movement is blocked
        void blockedMove();
        // shows the present state name
        void showState();
        
private:
        // gets target speed for drive stage
        void setDriveSpeed(float dist);
        // gets target speed for approach stage
        void setApproachSpeed(float dist);
        // gets the proper actions to reach the target speed
        void controlSpeed();
};
}
#endif
