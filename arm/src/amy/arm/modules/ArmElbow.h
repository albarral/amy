#ifndef __AMY_ARM_ARMELBOW_H
#define __AMY_ARM_ARMELBOW_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/ArmDriver.h"
#include "amy/arm/bus/JointBus.h"
#include "amy/move/RadialDriver.h"
//#include "amy/utils/Record.h"   // tmp for analysis

namespace amy
{
// Behavior used to move the arm horizontally.
// It controls the HORIZONTAL SHOULDER angle to reach a pan target position.
// It derives from ArmDriver module.
class ArmElbow: public ArmDriver
{
private:
    // bus
    JointBus* pBusElbow;   // bus connection to EL joint
    // request
    float armRadius;          // requested joint position
    // control 
    float istElbow;                // measured joint position
    RadialDriver oRadialDriver;    // utility class used to drive the joint
    int elbowLimitReached;     // value indicating the movement is blocked (due to joint limits reached)    
    // output
    float elbowAccel;              // commanded acceleration 
    // aux
//    Record oRecord; // record to store the speed evolution in movement  (for analysis purpose)

public:
        ArmElbow();
        //~ArmElbow();
                       
        // record output for analysis
//       Record& getRecord() {return oRecord;};

private:       
        // prepare arm driver
        virtual void prepareDriver();
        // connect driver to specific joints
        virtual void connectDriver();
        // prepare movement
        virtual void prepareMove();
        // perform movement
        virtual void doMove();
        // read bus data
        virtual void senseBus();
        // write action commands to bus
        virtual void writeBus();

        void showMovementData();

};
}
#endif
