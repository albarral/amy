/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>

#include "amy/utils/module3.h"


namespace amy
{
// Constructor
Module3::Module3 ()
{    
    prevState = state = Module3::state_OFF;
    boffRequested = false;
    setFrequency(0.1);  // low default frequency
}

void Module3::on()
{
    // only launch thread if in OFF state
    if (getState() == Module3::state_OFF)
    {
      t = std::thread(&Module3::run, this);              
    }           
}

void Module3::off()
{        
    std::lock_guard<std::mutex> locker(mutex);
    boffRequested = true;
}

bool Module3::offRequested()
{
    std::lock_guard<std::mutex> locker(mutex);
    if (boffRequested)
    {
        // reset flag when checked
        boffRequested = false;
        return true;
    }
    else
        return (false);        
}

void Module3::wait()
{
    t.join();
}

void Module3::setFrequency(float cps)
{
    std::lock_guard<std::mutex> locker(mutex);
    if (cps > 0.0)
    {
        period = 1000000/cps;    // in microseconds
        frequency = cps;
    }
}

float Module3::getFrequency()
{
    std::lock_guard<std::mutex> locker(mutex);
    return frequency;        
}

void Module3::run ()
{    
    // first escape from OFF (as setState() can't escape from it)
    state = Module3::state_UNKNOWN;
    first();
    while (!offRequested())
    {
        loop();
        // store previous value
        storePrevState();
        usleep(period);
    }
    
    // final state OFF
    setState(Module3::state_OFF);
}


int Module3::getState()
{
    std::lock_guard<std::mutex> locker(mutex);
    return (state);        
}

int Module3::getPrevState()
{
    std::lock_guard<std::mutex> locker(mutex);
    return (prevState);        
}

void Module3::setState(int state)
{
    std::lock_guard<std::mutex> locker(mutex);
    // only proceed when module not OFF
    if (this->state != Module3::state_OFF)
        this->state = state;    
}

void Module3::storePrevState()
{
    std::lock_guard<std::mutex> locker(mutex);
    prevState = state;
}

bool Module3::isStateChanged()
{
    std::lock_guard<std::mutex> locker(mutex);
    return (state != prevState);        
}

}

