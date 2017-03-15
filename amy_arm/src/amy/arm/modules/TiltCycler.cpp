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

void TiltCycler::senseBus()
{    
    // process frequency requests
    if (pArmBus->getCO_TILT_FREQUENCY().checkRequested())
    {
        frequency = pArmBus->getCO_TILT_FREQUENCY().getValue();
        oOscillator.setFrequency(frequency);
        // tune the movement speed
        tuneSpeed();
    }

    // process amplitude requests
    if (pArmBus->getCO_TILT_AMPLITUDE().checkRequested())
    {
        amplitude = pArmBus->getCO_TILT_AMPLITUDE().getValue();
        // tune the movement speed
        tuneSpeed();
    }
    
    if (pArmBus->getCO_TILT_TRIGGER().checkRequested())
        setState(eSTATE_START);                   

    if (pArmBus->getCO_TILT_STOP().checkRequested())
    {
        oOscillator.stop();
        setState(eSTATE_DONE);                   
    }
}

void TiltCycler::writeBus()
{  
    // control pan speed
    pArmBus->getCO_TILT_SPEED().request(outSpeed, priority);
}

}