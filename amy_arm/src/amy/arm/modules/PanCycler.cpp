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
    pBusPan = 0;
}

void PanCycler::tune2Axis()
{
    pBusPan = &pArmBus->getPanBus();
}

void PanCycler::senseBus()
{    
    // process frequency requests
    if (pBusPan->getCO_AXIS_FREQUENCY().checkRequested())
    {
        frequency = pBusPan->getCO_AXIS_FREQUENCY().getValue();
        oOscillator.setFrequency(frequency);
        // tune the movement speed
        tuneSpeed();
    }

    // process amplitude requests
    if (pBusPan->getCO_AXIS_AMPLITUDE().checkRequested())
    {
        amplitude = pBusPan->getCO_AXIS_AMPLITUDE().getValue();
        // tune the movement speed
        tuneSpeed();
    }
    
    if (pBusPan->getCO_AXIS_TRIGGER().checkRequested())
        setState(eSTATE_START);                   

    if (pBusPan->getCO_AXIS_STOP().checkRequested())
    {
        oOscillator.stop();
        setState(eSTATE_DONE);                   
    }
}

void PanCycler::writeBus()
{  
    // control pan speed
    pBusPan->getCO_AXIS_SPEED().request(outSpeed, priority);
}

}