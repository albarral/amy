#ifndef __AMY_ARM_TILTCYCLER_H
#define __AMY_ARM_TILTCYCLER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/AxisCycler.h"

namespace amy
{
// Module used to perform cyclic tilt movements.
// Derives from AxisCycler    
class TiltCycler: public AxisCycler
{       
public:
        TiltCycler();
        //~TiltCycler();                

private:
        // read bus data
        virtual void senseBus();
        // write info (control & sensory) to bus
        virtual void writeBus();        
};
}
#endif
