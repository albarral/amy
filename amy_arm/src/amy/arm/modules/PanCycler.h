#ifndef __AMY_ARM_PANCYCLER_H
#define __AMY_ARM_PANCYCLER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/AxisCycler.h"

namespace amy
{
// Module used to perform cyclic pan movements.
// Derives from AxisCycler    
class PanCycler: public AxisCycler
{       
public:
        PanCycler();
        //~PanCycler();                

private:
        // connect module to specific axis
        virtual void tune2Axis();        
};
}
#endif
