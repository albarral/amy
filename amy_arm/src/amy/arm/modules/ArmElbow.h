#ifndef __AMY_ARM_ARMELBOW_H
#define __AMY_ARM_ARMELBOW_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/ArmDriver.h"
#include "amy/arm/bus/JointBus.h"
#include "amy/arm/move/RadialDriver.h"
//#include "amy/utils/Record.h"   // tmp for analysis

namespace amy
{
// Behavior used to move the arm's elbow.
// It senses for arm radius requests (from bus) and controls the elbow angle to reach those radius.
// Derived from ArmDriver.
// Controlled joints:
// ELBOW (EL)        
class ArmElbow: public ArmDriver
{
private:
    // bus
    JointBus* pBusElbow;   // bus connection to EL joint
    // request
    float targetRadius;          // requested arm radius
    // control 
    float istElbow;                // measured elbow position
    RadialDriver oRadialDriver;    // utility class used to drive the elbow
    int elbowLimitReached;     // value indicating the elbow movement is blocked (due to reached joint limit)   
    // output
    float elbowAccel;              // commanded elbow acceleration 
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
};
}
#endif
