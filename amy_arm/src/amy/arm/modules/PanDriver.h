#ifndef __AMY_ARM_PANDRIVER_H
#define __AMY_ARM_PANDRIVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/AxisDriver.h"
#include "amy/arm/move/JointControl.h"

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
    JointControl oJointControl;      // utility class to drive the horizontal shoulder
    JointBus* pHSBus;   // bus connection to HS
    float istHS;               // measured HS angle

public:
        PanDriver();
        //~PanDriver();
                       
private:       
        // return reference to the used joint controller
        virtual JointControl& getController() {return oJointControl;};
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
