/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/control/Oscillator2.h"

namespace amy
{
Oscillator2::Oscillator2()
{    
    angularSpeed = 0.0;
    position = 0.0;
    signal = 0;
}

void Oscillator2::setFrequency(float freq)
{
    // only positive frequencies are valid
    if (freq > 0.0)
    {        
        // set speed to make a whole lap in each period
        angularSpeed = 360.0*freq/1000; 
        frequency = freq;
    }
};

void Oscillator2::reset()
{
    // starts new oscillation     
    position = 0.0;
    signal = 0.0;
    // and starts chronometer
    oClick.start();
}

float Oscillator2::update()
{
    // compute elapsed time 
    oClick.read();
    oClick.start();        
    // update signal 
    position += angularSpeed * oClick.getMillis();
    
    // if lap completed, follow in new lap (while used for if various laps passed)
    while (position >= 360.0)
        position = 360.0 - position;
    
    // signal changes every 90 degrees
    signal = (int)(position/90);
    
    return signal;
}

void Oscillator2::stop()
{
    angularSpeed = 0.0;
}
}