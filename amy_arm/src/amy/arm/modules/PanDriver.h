#ifndef __AMY_ARM_PANDRIVER_H
#define __AMY_ARM_PANDRIVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/AxisDriver.h"
#include "amy/arm/move/JointControl.h"
//#include "amy/utils/Record.h"   // tmp for analysis

namespace amy
{
// Behavior used to move the arm's pan.
// It responds to arm pan requests (from bus) and controls the horizonal shoulder angle to reach those pans.
// Derived from AxisDriver.
// Controlled joints:
// HORIZONTAL SHOULDER (HS)    
class PanDriver: public AxisDriver
{
private:
    JointControl oJointControl;      // utility class to drive the horizontal shoulder
    // aux
//    Record oRecord; // record to store the speed evolution in movement  (for analysis purpose)

public:
        PanDriver();
        //~PanDriver();
                       
        // record output for analysis
//       Record& getRecord() {return oRecord;};

private:       
        // return reference to the used joint controller
        virtual JointControl& getController() {return oJointControl;};
        // connect driver to specific joint
        virtual void connectOutput();
        // read bus data
        virtual void senseBus();
        // prepare movement
        virtual void updateTarget();

        void showMovementData();

};
}
#endif
