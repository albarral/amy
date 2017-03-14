#ifndef __AMY_CONTROL_OSCILLATOR_H
#define __AMY_CONTROL_OSCILLATOR_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/control/Click.h"

namespace amy
{
// Class that simulates a linear oscillator.
// The signal value oscillates continously between -1 and 1 at the requested frequency.
// On trigger the oscillation restarts with signal 0 and positive direction.
class Oscillator
{
private:
    // parameter
    float frequency;     // oscillation frequency (Hz))
    // logic
    float speed;     // speed at which the signal changes (units/ms)  (depends on the frequency)
    int direction;    // direction of signal change              
    float signal;     // the oscillating value [-1, 1]
    Click oClick;     // clock utility to measure times

public:
    Oscillator();

    // sets the oscillator frequency
    void setFrequency(float freq);
    float getFrequency() {return frequency;};
    
    // resets the oscillator
    void trigger();
    // runs the oscillator (modifies the signal according to the elapsed time)
    float run();
    // stops the oscillator
    void stop();
    // gets the present signal value
    float getSignal() {return signal;}
        
};
}
#endif
