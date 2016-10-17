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
    // logic
    float targetSpeed;    // desired arm speed
    float sollSpeed;         // real arm speed
    float istPos;            // real axis position
    int maxAccel;          // central max acceleration
    bool bnewRequest;    // flag indicating new move requested
    float vDrive;             // drive speed 
    float vApproach;       // approach speed
    float dBrake;           // distance needed to brake at maximum acceleration
    int blockedTime;     // time that movement has been blocked (ie for limit reasons)
    // tolerances
    float speedTol;         // tolerance allowed around target speed 
    float posTol;            // tolerance allowed around final position

public:
        AxisDriver2();
        //~AxisDriver2();
                
       // module params
       void init(float tolPos, float tolSpeed, int vApproach, MovementControl& oMovementControl);
       bool isEnabled() {return benabled;};

       // bus connection 
       void connect(ArmBus& oBus);
       bool isConnected() {return bconnected;};
                      
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

        // prepares for new move
        void newMove(float dist);
        // updates the target speed
        void updateTargetSpeed(float speed, float dist);
        // computes the position tolerance
        void updatePosTolerance(float dist);

        // gets the proper actions to reach the target speed
        void controlSpeed();
};
}
#endif
