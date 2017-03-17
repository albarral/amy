/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/TiltCycler.h"

namespace amy
{
TiltCycler::TiltCycler()
{
    modName = "TiltCycler";
}

void TiltCycler::tune2Axis()
{
    // bus connection to tilt axis
    pAxisBus = &pArmBus->getTiltBus();
}
}