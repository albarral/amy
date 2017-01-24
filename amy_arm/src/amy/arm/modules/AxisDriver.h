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
#include "amy/core/config/JointControlConfig.h"
#include "amy/core/robot/Arm.h"
#include "amy/utils/module3.h"

namespace amy
{
// Base module for driving a given arm axis (pan, tilt, radius) in response to position commands. 
// The module outputs controls to a single joint.    
// The module's loop works as follows:
// - senses the bus
// - responds to new move requests
// - performs move steps iteratively ...
// - until movement is finished or blocked by any cause.
// - States: 
// DRIVE:        moves the arm
// DONE:        nothing done
class AxisDriver: public Module3
{
public:
    // states of AxisDriver module
    enum eType
    {
         eSTATE_DONE,
         eSTATE_DRIVE
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
    JointBus* pJointBus;   // bus connection to output joint
    // request
    float targetValue;           // requested axis position
    // control 
    float istJoint;                  // measured joint position
    int jointLimit;     // value indicating the axis movement is blocked (due to reached joint limit)   
    // output
    float outAccel;              // commanded joint acceleration 

private:    
    // logic
    bool bnewMove;          // flag indicating new move requested
    bool bmoveBlocked;    // flag indicating the move is blocked
    bool bmoveDone;        // flag indicating the move is done

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
        // connect driver to specific joint
        virtual void connectOutput() = 0;
        // prepare axis driver
        virtual void prepareDriver();
        // perform movement
        void doMove();
        // read bus data
        virtual void senseBus() = 0;
        // prepare movement
        virtual void updateTarget() = 0;
        // write action commands to out joint bus
        void writeBus();
        
        // raises flag for new move
        void moveRequested();
        // raises flag for blocked move 
        void moveBlocked();
        // raises flag for done move
        void moveDone();
        
private:
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
                
        // prepare for new movement
        void newMove();
        // movement finished
        void done();
                        
        // shows the present state name
        void showState();
};
}
#endif
