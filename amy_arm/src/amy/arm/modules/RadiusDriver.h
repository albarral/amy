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
// Controlled joints:
// ELBOW (ELB)    
class RadiusDriver: public AxisDriver
{
private:
    RadialControl oRadialControl;      // utility class to drive the ELB

public:
        RadiusDriver();
        //~RadiusDriver();
                       

private:       
        // return reference to the used joint controller
        virtual JointControl& getController() {return oRadialControl;};
        // prepare arm driver
        virtual void prepareDriver();
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
