#ifndef __AMY_ARM_ARMPANNER_H
#define __AMY_ARM_ARMPANNER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/AxisDriver.h"

namespace amy
{
// Behavior used to move the arm horizontally.
// It controls the HORIZONTAL SHOULDER angle to reach a pan target position.
// It's an AxisDriver module.
class ArmPanner: public AxisDriver
{
public:
        ArmPanner();
        //~ArmPanner();
                                      
private:       
        virtual void selectBusJoint();        
        // read bus data
        virtual void senseBus();
        // write action commands to bus
        virtual void writeBus();
        
};
}
#endif
