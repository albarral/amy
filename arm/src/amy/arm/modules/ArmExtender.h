#ifndef __AMY_ARM_ARMEXTENDER_H
#define __AMY_ARM_ARMEXTENDER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/arm/modules/AxisDriver3.h"

namespace amy
{
// Behaviour used to extend the arm.
// It controls the ELBOW angle to reach a radial target position.
// It's an AxisDriver module.
class ArmExtender: public AxisDriver3
{
public:
        ArmExtender();
        //~ArmExtender();
                                      
private:       
        virtual void selectBusJoint();
        
        // read bus data
        virtual void senseBus();
        // write action commands to bus
        virtual void writeBus();
        
};
}
#endif
