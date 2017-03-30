#ifndef __AMY_ARM_RADIUSDRIVER_H
#define __AMY_ARM_RADIUSDRIVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/bus/AxisBus.h"
#include "amy/arm/modules/AxisDriver.h"
#include "amy/arm/move/RadialPositioner.h"

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
    RadialPositioner oRadialPositioner;      // utility class to drive the ELB
    float istEL;               // measured EL angle

public:
        RadiusDriver();
        //~RadiusDriver();
                       

private:       
        // return reference to the used joint controller
        virtual JointPositioner& getController() {return oRadialPositioner;};
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
