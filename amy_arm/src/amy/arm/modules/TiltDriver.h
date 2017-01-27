#ifndef __AMY_ARM_TILTDRIVER_H
#define __AMY_ARM_TILTDRIVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/AxisDriver.h"
#include "amy/arm/move/JointControl.h"
#include "amy/arm/move/ArmMath.h"

namespace amy
{
// Behavior used to move the arm's tilt.
// It responds to arm tilt requests (from bus) and controls the vertical shoulder angle to reach those tilts.
// Derived from AxisDriver.
// Controlled joint:
// VERTICAL SHOULDER (VS)    
class TiltDriver: public AxisDriver
{
private:
    JointControl oJointControl;      // utility class to drive the VS
    ArmMath oArmMath;       // utility class for arm computations
    JointBus* pVSBus;       // bus connection to VS
    float istVS;               // measured VS angle
    JointBus* pELBus;       // bus connection to EL
    float istEL;               // measured EL angle

public:
        TiltDriver();
        //~TiltDriver();

private:       
        // return reference to the used joint controller
        virtual JointControl& getController() {return oJointControl;};
        // prepare axis driver
        virtual void prepareDriver();
        // connect driver to specific joint
        virtual void connectJoints();
        // read bus data
        virtual void senseBus();
        // prepare movement
        virtual void newMove();
        // computes the axis position
        virtual void computeAxisPosition();

        void showMovementData();

};
}
#endif
