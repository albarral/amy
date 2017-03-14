/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/control/Oscillator.h"

namespace amy
{
Oscillator::Oscillator()
{    
    speed = 0.0;
    direction = 0.0; 
    signal = 0.0;
}

void Oscillator::setFrequency(float freq)
{
    if (freq > 0.0)
    {        
        // on each period the signal must change 4 units (from 1 to -1, and back from -1 to 1)
        speed = 4.0*freq/1000; //period = 1000.0/freq;
        frequency = freq;
    }
};

void Oscillator::trigger()
{
    // starts new oscillation
    signal = 0.0;
    direction = 1;
    // and starts chronometer
    oClick.start();
}

float Oscillator::run()
{
    // compute elapsed time 
    oClick.read();
    oClick.start();        
    // update signal 
    signal += speed * direction * oClick.getMillis();
    
    // if signal arrived at its end, change direction and advance the proper amount
    if (fabs(signal) >= 1.0)
    {
        direction = (direction == 1 ? -1 : 1);
        // measure excess
        float excess = fabs(signal) - 1.0;
        
        // if excess is bigger than signal's amplitude transform it to direction changes
        while (excess > 2.0)
        {
            direction = (direction == 1 ? -1 : 1);
            excess -= 2.0;
        }
        // advance signal the residual excess
        if (direction > 0)
            signal = -1.0 + excess;
        else
            signal = 1.0 - excess;                            
    }
    return signal;
}

void Oscillator::stop()
{
    signal = 0.0;
    speed = 0.0;
}
}