#ifndef __AMY_CONTROL_OSCILLATOR2_H
#define __AMY_CONTROL_OSCILLATOR2_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/control/Click.h"

namespace amy
{
// Class that simulates a circular oscillator.
// The oscillator position advances from 0 to 360 degrees in the requested period. Then continues with next lap (starting at 0).
// The output signal depends on the actual position, and goes from 0 to 3 at 90 degree intervals.
// On reset the oscillator position is set at 0.
class Oscillator2
{
private:
    // parameter
    float frequency;     // oscillation frequency (Hz))
    float angularSpeed;     // speed at which the position changes (degrees/ms)  (depends on the frequency)
    // logic
    float position;     // oscillator position (degrees)
    int signal;          // the oscillating value [0, 3] (90 degree intervals)
    Click oClick;     // clock utility to measure times

public:
    Oscillator2();

    // sets the oscillator frequency
    void setFrequency(float freq);
    float getFrequency() {return frequency;};
    
    // resets the oscillator
    void reset();
    // updates the oscillator position (and signal) according to the elapsed time
    float update();
    // stops the oscillator
    void stop();
    
    // gets the present signal value
    int getSignal() {return signal;};        
    int getPosition() {return position;};
        
};
}
#endif
