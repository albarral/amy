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
// Movements done in 3 stages: 
// DRIVE:           high speed      (far from target))
// APPROACH;    lower speed    (near to target)
// ARRIVED:        stop               (at target, with tolerance)  
// FREE:            (special state) leaves arm free, no control done
// 4 params:
// dH: distance that separates DRIVE & APPROACH states
// dL: pos tolerance for ARRIVED state
// vDrive: high speed used on DRIVE
// vApproach: low speed used on APPROACH
// tolerance: tolerance for speed control    
// Outputs:
// DRIVE:             PUSH_FRONT, PUSH_BAC, KEEP
// APPROACH:      KEEP, nothing
// ARRIVED:          nothing
class AxisDriver: public Module2
{
public:
    // states of AxisDriver module
    enum eType
    {
         eSTATE_FREE,
         eSTATE_ARRIVED,
         eSTATE_APPROACH,
         eSTATE_DRIVE
    };

protected:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    std::string modName;   // module name
    // params
    int dH;     // drive threshold distance
    int dL;     // arrived threshold distance
    int vDrive;     // drive speed 
    int vApproach;     // approach speed
    float tolerance;    // tolerance in speed control
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pBus;
    JointBus* pJointBus;   // bus connection to a joint
    // logic
    int targetPos;          // desired axis position
    float istPos;            // real axis position
    float istSpeed;         // real arm speed
    int outAction;          // commanded action to JMover modules
    bool bsendAction;   // flag to indicate action must be sent
    // aux
    int vDriveTol;          // drive speed tolerance (deg/s))
    int vApproachTol;   // approach speed tolerance (deg/s))            

public:
        AxisDriver();
        //~AxisDriver();
                
       // module params
       void init(int dH, int dL, int vDrive, int vApproach, float tolerance);
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

        // move joint to target position at drive speed
        void doDrive(float dist);
        // move joint to target position at approach speed
        void doApproach(float dist);
        // stop joint movement
        void doArrived(float dist);
        
        // shows the present state name
        void showState();
};
}
#endif
