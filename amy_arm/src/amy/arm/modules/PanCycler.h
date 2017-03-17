#ifndef __AMY_ARM_PANCYCLER_H
#define __AMY_ARM_PANCYCLER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/bus/AxisBus.h"
#include "amy/arm/modules/AxisCycler.h"

namespace amy
{
// Module used to perform cyclic pan movements.
// Derives from AxisCycler    
class PanCycler: public AxisCycler
{       
private:    
    // bus
    AxisBus* pBusPan;    // bus connection to pan axis

public:
        PanCycler();
        //~PanCycler();                

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
