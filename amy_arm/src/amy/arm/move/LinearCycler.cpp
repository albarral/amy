/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/move/LinearCycler.h"

namespace amy
{
LinearCycler::LinearCycler()
{
    freq = 0.0;
    angle = 0.0;     
    amplitude = 0.0;
    movSpeed = 0.0;
}

void  LinearCycler::setFreq(float value) 
{
    // set frequency of triangular signal 
    oTriangularSignal.setFrequency(value);
    // get changed value
    freq = oTriangularSignal.getFrequency();
    // redefine movement speed
    redefine();
}

void  LinearCycler::setAngle(float value)
{
    angle = value;
    // reorient speed vector
    oSpeedVector.setAngle(value);
}

void  LinearCycler::setAmp(float value)
{
    amplitude = value;
    // redefine movement speed
    redefine();
}

void  LinearCycler::setPhase(int value)
{
    // set phase of triangular signal
    oTriangularSignal.setPhase(value);
    // get changed value
    phase = oTriangularSignal.getPhase();
}

// triggers a cyclic movement
void LinearCycler::trigger(maty::Clock& oClock)
{
    // trigger new oscillation            
    oTriangularSignal.start(oClock);
    oSpeedVector.updateMagnitude(0.0);
}
                    
void LinearCycler::redefine()
{
    // on each period the amplitude must be walked twice
    float avgSpeed = 2.0*amplitude*freq;    
    // in a triangular signal the top speed is twice the average speed
    movSpeed = 2.0*avgSpeed;
}

// update the cyclic movement
void LinearCycler::update(maty::Clock& oClock)
{
    // modulate speed as a triangular signal
    // and decompose it in x & y speeds
    float magnitude = movSpeed * oTriangularSignal.update(oClock);
    oSpeedVector.updateMagnitude(magnitude);
}

std::string LinearCycler::toString()
{
    std::string desc = "LinearCycler:[freq = " + std::to_string(freq) + ", angle = " + std::to_string(angle) + ", amplitude = " + std::to_string(amplitude) + "]";                        
    return desc;
}

}