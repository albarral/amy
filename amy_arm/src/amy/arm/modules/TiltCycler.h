#ifndef __AMY_ARM_TILTCYCLER_H
#define __AMY_ARM_TILTCYCLER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/bus/AxisBus.h"
#include "amy/arm/modules/AxisCycler.h"

namespace amy
{
// Module used to perform cyclic tilt movements.
// Derives from AxisCycler    
class TiltCycler: public AxisCycler
{       
private:    
    // bus
    AxisBus* pBusTilt;    // bus connection to tilt axis

public:
        TiltCycler();
        //~TiltCycler();                

private:
        // connect module to specific axis
        virtual void tune2Axis();        
        // read bus data
        virtual void senseBus();
        // write info (control & sensory) to bus
        virtual void writeBus();        
};
}
#endif
