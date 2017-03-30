/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/PanCycler.h"

namespace amy
{
PanCycler::PanCycler()
{
    modName = "PanCycler";
}

void PanCycler::tune2Axis()
{
    // bus connection to pan axis
    pAxisBus = &pArmBus->getPanBus();
}

}