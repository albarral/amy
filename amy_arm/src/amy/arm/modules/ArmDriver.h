#ifndef __AMY_ARM_ARMDRIVER_H
#define __AMY_ARM_ARMDRIVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/bus/ArmBus.h"
#include "amy/core/config/JointControlConfig.h"
#include "amy/core/robot/Arm.h"
#include "amy/utils/module3.h"

namespace amy
{
// Generic base module used to drive the arm. Can be used to control a single or multiple joints at once.
// It's a skeleton module that:
// - senses the bus
// - responds to new move requests
// - performs move steps iteratively ...
// - until movement is finished or blocked by any cause.
// - States: 
// DRIVE:        moves the arm
// DONE:        nothing done
class ArmDriver: public Module3
{
public:
    // states of ArmDriver module
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
    ArmBus* pArmBus;     // access to arm bus
    JointControlConfig* pJointControlConfig;  // control config
    // config
    Arm* pArm;              // arm physical data
private:    
    // logic
    bool bnewMove;          // flag indicating new move requested
    bool bmoveBlocked;    // flag indicating the move is blocked
    bool bmoveDone;        // flag indicating the move is done

public:
        ArmDriver();
        //~ArmDriver();
                
       // module params
       void init(Arm& oArm, JointControlConfig& oJointControlConfig);
       bool isEnabled() {return benabled;};

       // bus connection 
       void connect(ArmBus& oArmBus);
       bool isConnected() {return bconnected;};

                      
protected:               
        // prepare arm driver
        virtual void prepareDriver() {};
        // connect driver to specific joints
        virtual void connectDriver() {};
        // prepare movement
        virtual void prepareMove() = 0;
        // perform movement
        virtual void doMove() = 0;
        // read bus data
        virtual void senseBus() = 0;
        // write action commands to bus
        virtual void writeBus() = 0;
        
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
