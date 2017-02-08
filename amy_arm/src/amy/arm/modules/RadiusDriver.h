#ifndef __AMY_ARM_RADIUSDRIVER_H
#define __AMY_ARM_RADIUSDRIVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/AxisDriver.h"
#include "amy/arm/move/RadialControl.h"

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
    RadialControl oRadialControl;      // utility class to drive the ELB
    JointBus* pELBus;       // bus connection to EL
    float istEL;               // measured EL angle

public:
        RadiusDriver();
        //~RadiusDriver();
                       

private:       
        // return reference to the used joint controller
        virtual JointControl& getController() {return oRadialControl;};
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
