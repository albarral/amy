#ifndef __AMY_ARM_AXISDRIVER_H
#define __AMY_ARM_AXISDRIVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/move/JointControl.h"
#include "amy/core/MoveState.h"
#include "amy/core/config/JointControlConfig.h"
#include "amy/core/robot/Arm.h"
#include "amy/utils/module3.h"

namespace amy
{
// Base module for driving a given axis (pan, tilt, radius) to a requested position.
// The module can sense various joints, but only controls one (sends commands to one).
// KEEP MODE: In this mode the module stays watching out for any external change to the axis. If it changes a movement is triggered to recover the last target position.
// The module's loop works as follows:
// - senses the bus
// - responds to new move requests
// - performs move steps iteratively ...
// - until movement is finished or blocked by any cause.
class AxisDriver: public Module3
{
public:
    // states of AxisDriver module
    enum eType
    {
         eSTATE_DONE,     // nothing done
         eSTATE_DRIVE,     // moves the arm
         eSTATE_WATCH     // watches out for external axis changes
    };

protected:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    // config
    JointControlConfig* pJointControlConfig;  // control config
    Arm* pArm;              // arm physical data    
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pArmBus;     // access to arm bus
    JointBus* pOutBus;   // bus connection to controlled joint
    // control 
    float targetAxis;           // requested axis position
    float istAxis;                 // measured axis position
    float tolAxis;                  // allowed axis tolerance in keep mode
    int jointLimit;                 // value indicating the controlled joint is blocked (due to a reached joint limit)   
    bool bKeepMode;        // keep mode activation
    // output
    float outAccel;              // commanded joint acceleration 
    // logic
    MoveState oMoveState;   // holds the present move state

private:
    
public:
        AxisDriver();
        //~AxisDriver();
                
       // module params
       void init(Arm& oArm, JointControlConfig& oJointControlConfig);
       bool isEnabled() {return benabled;};

       // bus connection 
       void connect(ArmBus& oArmBus);
       bool isConnected() {return bconnected;};

                      
protected:
        // return reference to the used joint controller
        virtual JointControl& getController() = 0;
        // connect driver to specific joints
        virtual void connectJoints() = 0;
        // prepare axis driver
        virtual void prepareDriver();
        // read bus data
        virtual void senseBus() = 0;
        // prepare movement
        virtual void newMove() = 0;
        // computes the axis position
        virtual void computeAxisPosition() = 0;
        // set keep mode
        void setKeepMode(bool value) {bKeepMode = value;};
        //bool isKeepMode() {return bKeepMode;};
        
private:
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            

        // perform movement
        void doMove();        
        // write action commands to out joint bus
        void writeBus();
                                        
        // shows the present state name
        void showState();
};
}
#endif
