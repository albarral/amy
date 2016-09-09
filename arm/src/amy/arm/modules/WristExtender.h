#ifndef __AMY_ARM_WRIST_EXTENDER_H
#define __AMY_ARM_WRIST_EXTENDER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/modules/AxisDriver.h"
#include "amy/arm/bus/JointBus.h"

namespace amy
{
// Behaviour used to extend the arm.
// It controls the ELBOW angle to reach a radial target position.
// It's an WristExtender module (movements with 3 stages) 
class WristExtender: public AxisDriver
{
private:
    // bus
    JointBus* pBusEL;   // bus connection to ELBOW joint
    // logic
    float lastSollAngle;  // last commanded elbow angle
    int lastAction;     // last commanded elbow action    
    int lastSpeed;       // last commanded elbow speed


public:
        WristExtender();
        //~WristExtender();
                                      
private:       
        virtual void selectBusJoint();
        
        // read bus data
        virtual void senseBus();
        // write action commands to bus
        virtual void writeBus();
        
        virtual void doDriveControl(float dist);
        virtual void doApproachControl(float dist);
        virtual void doArrivedControl(float dist);
};
}
#endif
