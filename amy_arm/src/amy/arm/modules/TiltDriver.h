#ifndef __AMY_ARM_TILTDRIVER_H
#define __AMY_ARM_TILTDRIVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/bus/AxisBus.h"
#include "amy/arm/modules/AxisDriver.h"
#include "amy/arm/move/JointPositioner.h"
#include "amy/math/ArmMath.h"

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
    // bus
    AxisBus* pBusTilt;    // bus connection to tilt axis
    JointBus* pELBus;       // additional bus connection to EL (for axis position computation)
    JointPositioner oJointPositioner;      // utility class to drive the VS
    ArmMath oArmMath;       // utility class for arm computations
    float istVS;               // measured VS angle
    float istEL;               // measured EL angle

public:
        TiltDriver();
        //~TiltDriver();

private:       
        // return reference to the used joint controller
        virtual JointPositioner& getController() {return oJointPositioner;};
        // prepare axis driver
        virtual void prepareDriver();
        // connect driver to specific joint
        virtual void setControlledJoint();
        // read bus data
        virtual void senseBus();
        // prepare movement
        virtual void setNewTarget();
        // computes the axis position
        virtual void computeAxisPosition();

        void showMovementData();

};
}
#endif
