#ifndef __AMY_ARM_ARMPANNER_H
#define __AMY_ARM_ARMPANNER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/ArmDriver.h"
#include "amy/arm/bus/JointBus.h"
#include "amy/arm/move/JointControl.h"
//#include "amy/utils/Record.h"   // tmp for analysis

namespace amy
{
// Behavior used to move the arm horizontally.
// It senses for arm pan requests (from bus) and controls the horizonal shoulder angle to reach those pans.
// Derived from ArmDriver.
// Controlled joints:
// HORIZONTAL SHOULDER (HS)    
class ArmPanner2: public ArmDriver
{
private:
    // bus
    JointBus* pBusHS;   // bus connection to HS joint
    // request
    float targetPan;          // requested arm pan 
    // control 
    float istPan;                // measured pan position
    JointControl oJointControl;      // utility class to drive the horizontal shoulder
    int panLimitReached;     // value indicating the horizontal shoulder movement is blocked (due to reached joint limit)
    // output
    float panAccel;              // commanded horizontal shoulder acceleration 
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
