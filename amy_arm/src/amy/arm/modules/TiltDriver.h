#ifndef __AMY_ARM_TILTDRIVER_H
#define __AMY_ARM_TILTDRIVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/core/bus/AxisBus.h"
#include "amy/arm/modules/AxisDriver.h"
#include "tron/math/ArmMath.h"

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
    tron::ArmMath oArmMath;       // utility class for arm computations
    float istVS;               // measured VS angle
    float istEL;               // measured EL angle

public:
        TiltDriver();
        //~TiltDriver();

private:       
        // create proper joint controllers
        virtual void createControllers(Arm& oArm) override;
        // connect driver to specific joint
        virtual void setControlledJoint();
        // read bus data
        virtual void senseBus();
        // computes the axis position
        virtual float computeAxisPosition() override;

        void showMovementData();

};
}
#endif
