#ifndef __AMY_ARM_TILTRACER_H
#define __AMY_ARM_TILTRACER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/bus/JointBus.h"
#include "amy/arm/modules/AxisRacer.h"

namespace amy
{
// Behavior used to move the arm's tilt at a requested speed..
// Controlled joint:
// VERTICAL SHOULDER (VS)    
class TiltRacer: public AxisRacer
{
private:    
    // bus
    JointBus* pVSBus;      // bus connection to VS joint
    
public:
        TiltRacer();
        //~TiltRacer();
                       
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
