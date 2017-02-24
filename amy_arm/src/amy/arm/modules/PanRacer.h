#ifndef __AMY_ARM_PANRACER_H
#define __AMY_ARM_PANRACER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/bus/JointBus.h"
#include "amy/arm/modules/AxisRacer.h"

namespace amy
{
// Behavior used to move the arm's pan at a requested speed..
// Controlled joint:
// HORIZONTAL SHOULDER (HS)    
class PanRacer: public AxisRacer
{
private:    
    // bus
    JointBus* pHSBus;      // bus connection to HS joint
    
public:
        PanRacer();
        //~PanRacer();
                       
private:       
        // connect module to specific joint
        virtual void setControlledJoint();    
        // read bus data
        virtual void senseBus();
        // write info (control & sensory) to bus
        virtual void writeBus();
        
};
}
#endif
