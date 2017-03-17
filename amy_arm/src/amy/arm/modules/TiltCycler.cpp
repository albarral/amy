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
    pBusTilt = 0;
}

void TiltCycler::tune2Axis()
{
    pBusTilt = &pArmBus->getTiltBus();
}

void TiltCycler::senseBus()
{    
    // process frequency requests
    if (pBusTilt->getCO_AXIS_FREQUENCY().checkRequested())
    {
        frequency = pBusTilt->getCO_AXIS_FREQUENCY().getValue();
        oOscillator.setFrequency(frequency);
        // tune the movement speed
        tuneSpeed();
    }

    // process amplitude requests
    if (pBusTilt->getCO_AXIS_AMPLITUDE().checkRequested())
    {
        amplitude = pBusTilt->getCO_AXIS_AMPLITUDE().getValue();
        // tune the movement speed
        tuneSpeed();
    }
    
    if (pBusTilt->getCO_AXIS_TRIGGER().checkRequested())
        setState(eSTATE_START);                   

    if (pBusTilt->getCO_AXIS_STOP().checkRequested())
    {
        oOscillator.stop();
        setState(eSTATE_DONE);                   
    }
}

void TiltCycler::writeBus()
{  
    // control pan speed
    pBusTilt->getCO_AXIS_SPEED().request(outSpeed, priority);
}

}