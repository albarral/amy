#ifndef __AMY_ARM_AXISDRIVER_H
#define __AMY_ARM_AXISDRIVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/core/bus/ArmBus.h"
#include "amy/arm/move/JointPositioner.h"
#include "amy/arm/config/ArmConfig.h"
#include "amy/core/robot/Arm.h"
#include "tuly/control/module3.h"

namespace amy
{
// Base module for driving a given axis (pan, tilt, radius) to a requested position.
// The module can sense various joints, but only controls one (sends commands to one).
// The module's loop works as follows:
// - senses the bus
// - responds to new move requests
// - performs move steps iteratively ...
// - until movement is finished or blocked by any cause.
class AxisDriver: public tuly::Module3
{
public:
    // states of AxisDriver module
    enum eState
    {
         eSTATE_DONE,           // movement finished (nothing done)
         eSTATE_NEWMOVE,     // prepares new move
         eSTATE_DRIVE,           // moves the arm
         eSTATE_BLOCKED,      // movement blocked
    };

protected:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    // config
    ArmConfig* pArmConfig;  // control config
    Arm* pArm;              // arm physical data    
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pArmBus;     // access to arm bus
    JointBus* pJointBus;   // bus connection to controlled joint
    // control 
    float targetAxis;           // requested axis position
    float istAxis;                 // measured axis position
    int jointLimit;                 // value indicating the controlled joint is blocked (due to reached limit)   
    // output
    float outAccel;              // commanded joint acceleration 
    int priority;                   // module's priority in control commands
    
public:
        AxisDriver();
        //~AxisDriver();
                
       // module params
       void init(Arm& oArm, ArmConfig& oArmConfig);
       bool isEnabled() {return benabled;};

       // bus connection 
       void connect(ArmBus& oArmBus);
       bool isConnected() {return bconnected;};

                      
protected:
        // return reference to the used joint controller
        virtual JointPositioner& getController() = 0;
        // connect driver to specific joints
        virtual void setControlledJoint() = 0;
        // prepare axis driver
        virtual void prepareDriver();
        // read bus data
        virtual void senseBus() = 0;
         // prepare movement
        virtual void setNewTarget() = 0;
       // computes the axis position
        virtual void computeAxisPosition() = 0;
        
private:
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        // write info (control & sensory) to bus
        virtual void writeBus();
        // perform movement. Return false if movement done
        bool doMove();                                                
        // check if controlled joint is blocked (due to reached range limit)
        bool checkBlocked();                                                
        // shows the present state name
        void showState();
};
}
#endif
