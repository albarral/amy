#ifndef __AMY_ARM_RADIUSDRIVER_H
#define __AMY_ARM_RADIUSDRIVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/core/bus/AxisBus.h"
#include "amy/arm/modules/AxisDriver.h"

namespace amy
{
// Behavior used to move the arm's radius.
// It responds to arm radius requests (from bus) and controls the elbow angle to reach those radius.
// Derived from AxisDriver.
// Controlled joint:
// ELBOW (ELB)    
class RadiusDriver: public AxisDriver
{
private:
    AxisBus* pBusRadial;    // bus connection to radial axis
    float istEL;               // measured EL angle

public:
        RadiusDriver();
        //~RadiusDriver();
                       

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
