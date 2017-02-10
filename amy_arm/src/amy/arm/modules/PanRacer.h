#ifndef __AMY_ARM_PANRACER_H
#define __AMY_ARM_PANRACER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/AxisRacer.h"

namespace amy
{
// Behavior used to move the arm's pan at a given speed.
// Controls the horizonal shoulder angle.
// Derived from AxisRacer.
// Controlled joint:
// HORIZONTAL SHOULDER (HS)    
class PanRacer: public AxisRacer
{
private:
    JointBus* pHSBus;   // bus connection to HS

public:
        PanRacer();
        //~PanRacer();
                       
private:       
        // read bus data
        virtual void senseBus();
        // write info (control & sensory) to bus
        virtual void writeBus();
        // connect module output to specific joint
        virtual void connectOutput();

};
}
#endif
