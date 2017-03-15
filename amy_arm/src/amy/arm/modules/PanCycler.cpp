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

void PanCycler::senseBus()
{    
    // process frequency requests
    if (pArmBus->getCO_PAN_FREQUENCY().checkRequested())
    {
        frequency = pArmBus->getCO_PAN_FREQUENCY().getValue();
        oOscillator.setFrequency(frequency);
        // tune the movement speed
        tuneSpeed();
    }

    // process amplitude requests
    if (pArmBus->getCO_PAN_AMPLITUDE().checkRequested())
    {
        amplitude = pArmBus->getCO_PAN_AMPLITUDE().getValue();
        // tune the movement speed
        tuneSpeed();
    }
    
    if (pArmBus->getCO_PAN_TRIGGER().checkRequested())
        setState(eSTATE_START);                   

    if (pArmBus->getCO_PAN_STOP().checkRequested())
    {
        oOscillator.stop();
        setState(eSTATE_DONE);                   
    }
}

void PanCycler::writeBus()
{  
    // control pan speed
    pArmBus->getCO_PAN_SPEED().request(outSpeed, priority);
}

}