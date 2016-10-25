#ifndef __AMY_ARM_ARMPANNER2_H
#define __AMY_ARM_ARMPANNER2_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/AxisDriver3.h"
#include "amy/arm/bus/JointBus.h"

namespace amy
{
// Behavior used to move the arm horizontally.
// It controls the HORIZONTAL SHOULDER angle to reach a pan target position.
// It's an AxisDriver module.
class ArmPanner2: public AxisDriver3
{
private:
        JointBus* pBusHS;   // bus connection to HS joint

public:
        ArmPanner2();
        //~ArmPanner2();
                                      
private:       
        virtual void selectBusJoints();        
        // read bus data
        virtual void senseBus();
        // write action commands to bus
        virtual void writeBus();
        // computes distance to target
        virtual float computeDistance();                
     
};
}
#endif
