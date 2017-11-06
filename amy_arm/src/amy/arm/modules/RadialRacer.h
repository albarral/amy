#ifndef __AMY_ARM_RADIALRACER_H
#define __AMY_ARM_RADIALRACER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/core/bus/AxisBus.h"
#include "amy/core/bus/JointBus.h"
#include "amy/arm/modules/AxisRacer.h"

namespace amy
{
// Behavior used to move the arm's radius at a requested speed..
// Controlled joint:
// ELBOW (ELB)    
class RadialRacer: public AxisRacer
{
private:    
    // bus
    AxisBus* pBusRadial;    // bus connection to radial axis
    JointBus* pELBus;      // bus connection to ELB joint
    
public:
        RadialRacer();
        //~RadialRacer();
                       
private:       
        // connect module to specific joint
        virtual void setSpecificConnections();    
        // read bus data
        virtual void senseBus();
        // write info (control & sensory) to bus
        virtual void writeBus();
        
};
}
#endif
