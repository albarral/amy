#ifndef __AMY_ARM_ARMPANNER_H
#define __AMY_ARM_ARMPANNER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/ArmDriver.h"
#include "amy/arm/bus/JointBus.h"
#include "amy/move/JointDriver.h"
//#include "amy/utils/Record.h"   // tmp for analysis

namespace amy
{
// Behavior used to move the arm horizontally.
// It controls the HORIZONTAL SHOULDER angle to reach a pan target position.
// It derives from ArmDriver module.
class ArmPanner2: public ArmDriver
{
private:
    // bus
    JointBus* pBusHS;   // bus connection to HS joint
    // request
    float targetPan;          // requested joint position
    // control 
    float istPan;                // measured joint position
    JointDriver oJointDriver;      // utility class used to drive the joint
    int panLimitReached;     // value indicating the movement is blocked (due to joint limits reached)    
    // output
    float panAccel;              // commanded acceleration 
    // aux
//    Record oRecord; // record to store the speed evolution in movement  (for analysis purpose)

public:
        ArmPanner2();
        //~ArmPanner2();
                       
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
