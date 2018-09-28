#ifndef __AMY_ARM_PANDRIVER_H
#define __AMY_ARM_PANDRIVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/core/bus/AxisBus.h"
#include "amy/arm/modules/AxisDriver.h"

namespace amy
{
// Behavior used to move the arm's pan.
// It responds to arm pan requests (from bus) and controls the horizonal shoulder angle to reach those pans.
// Derived from AxisDriver.
// Controlled joint:
// HORIZONTAL SHOULDER (HS)    
class PanDriver: public AxisDriver
{
private:
    // bus
    AxisBus* pBusPan;    // bus connection to pan axis
    float istHS;               // measured HS angle

public:
        PanDriver();
        //~PanDriver();
                       
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
