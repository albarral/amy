#ifndef __AMY_ARM_AXISDRIVER_H
#define __AMY_ARM_AXISDRIVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/bus/ArmBus.h"
#include "amy/utils/module2.h"

namespace amy
{
// Behaviour used to move an arm to a target position in a single direction (pan, tilt or radial.
// BASE class to be extended ...   
// Movements done in 2 stages: 
// DRIVE:           high speed when far from target - low speed when near to target
// ARRIVED:        stop when target reached (with a tolerance)  
// - params:
// dNear: distance limit between near & far
// dTol: tolerance distance for target reached
// vHigh:       high speed used on DRIVE state
// vLow:        low speed used on DRIVE state
// speedTolerance:   tolerance for speed control    
// - Outputs:
// DRIVE:             PUSH_FRONT, PUSH_BAC, KEEP
// ARRIVED:          STOP
// DONE:             nothing
class AxisDriver: public Module2
{
public:
    // states of AxisDriver module
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
    int dNear;     // drive threshold distance
    int dTol;     // arrived threshold distance
    int vHigh;     // drive speed 
    int vLow;     // approach speed
    float speedTolerance;    // tolerance in speed control
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pBus;
    JointBus* pJointBus;   // bus connection to a joint
    // logic
    int targetPos;          // desired axis position
    float istPos;            // real axis position
    float istSpeed;         // real arm speed
    int outAction;          // commanded action to JMover modules
    int blockedTime;     // time that movement has been blocked (ie for limit reasons)
    // aux
    int tolvHigh;          // drive speed tolerance (deg/s)
    int tolvLow;            // approach speed tolerance (deg/s)            

public:
        AxisDriver();
        //~AxisDriver();
                
       // module params
       void init(int dNear, int dTol, int vHigh, int vLow, float speedTolerance);
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
        
        // starts new move
        void newMove();
        // move joint to target position at proper speed
        void doDrive(float dist, float absDist);
        // stop joint movement
        void doArrived();
        
        // movement is blocked
        void blockedMove();
        // shows the present state name
        void showState();
};
}
#endif
