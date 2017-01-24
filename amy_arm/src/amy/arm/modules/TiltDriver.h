#ifndef __AMY_ARM_TILTDRIVER_H
#define __AMY_ARM_TILTDRIVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/AxisDriver.h"
#include "amy/arm/move/JointControl.h"

namespace amy
{
// Behavior used to move the arm's tilt.
// It responds to arm tilt requests (from bus) and controls the vertical shoulder angle to reach those tilts.
// Derived from AxisDriver.
// Controlled joints:
// VERTICAL SHOULDER (VS)    
class TiltDriver: public AxisDriver
{
private:
    JointControl oJointControl;      // utility class to drive the VS

public:
        TiltDriver();
        //~TiltDriver();

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
