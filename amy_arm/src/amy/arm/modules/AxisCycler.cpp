/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include "log4cxx/ndc.h"

#include "amy/arm/modules/AxisCycler.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AxisCycler::logger(Logger::getLogger("amy.arm"));

AxisCycler::AxisCycler()
{
    modName = "AxisCycler";
    pAxisBus = 0;
    tunedSpeed = 0;
    // control priority
    priority = 1; //oArmConfig.getPriority4AxisCyclers();    
}

void AxisCycler::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}

void AxisCycler::first()
{
    // start at done
    setState(eSTATE_DONE);
    // connect to controlled axis (defined in derived modules)
    tune2Axis();

    log4cxx::NDC::push(modName);   	
}
                    
void AxisCycler::loop()
{
    bool bchangeOutput = false;
    
    senseBus();

    int state = getState();
    // skip if DONE 
    if (state == eSTATE_DONE)            
        return;
            
    switch (state)
    {
        case eSTATE_START:         
            // launch cyclic movement
            
            // trigger new oscillation            
            oOscillator.trigger();
            lastSignal = oOscillator.getSignal();
            
            // if amplitude defined -> GO 
            if (amplitude != 0.0)
                setState(eSTATE_GO);
            // otherwise, nothing to do -> DONE
            else
                setState(eSTATE_DONE);                            

            // show data
            LOG4CXX_INFO(logger, ">> new request");  
            LOG4CXX_INFO(logger, "freq = " << frequency << ", amplitude = " << amplitude);  
            break;  

        case eSTATE_GO:
            // do cycles

            // get oscillator signal
            signal = oOscillator.run();           
            // if signal sign changed, change out speed
            if (signal*lastSignal <= 0)
            {
                outSpeed = (signal > 0 ? tunedSpeed : -tunedSpeed);
                bchangeOutput = true;
                LOG4CXX_INFO(logger, " outSpeed=" + std::to_string(outSpeed));
            }        
            // store signal
            lastSignal = signal;
            break;

        case eSTATE_STOP:
            // stop movement

            // stop oscillator and command null speed 
            oOscillator.stop();
            outSpeed = 0.0;
            bchangeOutput = true;
            // then go to DONE
            setState(eSTATE_DONE);
            break;
    }   // end switch    

    if (isStateChanged())
        showState();

    if (bchangeOutput)
        writeBus();        
}

void AxisCycler::senseBus()
{    
    // process frequency requests
    if (pAxisBus->getCO_AXIS_FREQUENCY().checkRequested())
    {
        frequency = pAxisBus->getCO_AXIS_FREQUENCY().getValue();
        oOscillator.setFrequency(frequency);
        // tune the movement speed
        tuneSpeed();
    }

    // process amplitude requests
    if (pAxisBus->getCO_AXIS_AMPLITUDE().checkRequested())
    {
        amplitude = pAxisBus->getCO_AXIS_AMPLITUDE().getValue();
        // tune the movement speed
        tuneSpeed();
    }
    
    // trigger requested -> START state
    if (pAxisBus->getCO_AXIS_TRIGGER().checkRequested())
        setState(eSTATE_START);                   

    // stop requested -> STOP state
    if (pAxisBus->getCO_AXIS_STOP().checkRequested())
        setState(eSTATE_STOP);                   
}

void AxisCycler::writeBus()
{  
    // control axis speed
    pAxisBus->getCO_AXIS_SPEED().request(outSpeed, priority);
}

void AxisCycler::tuneSpeed()
{
    // tune the movement speed (twice the amplitude must be covered on each cycle)
    tunedSpeed = 2*fabs(amplitude)*frequency;    
}

void AxisCycler::showState()
{
    switch (getState())
    {
        case eSTATE_DONE:
            LOG4CXX_INFO(logger, ">> done");
            break;
                        
        case eSTATE_START:
            LOG4CXX_INFO(logger, ">> start");
            break;

        case eSTATE_GO:
            LOG4CXX_INFO(logger, ">> go");
            break;

        case eSTATE_STOP:
            LOG4CXX_INFO(logger, ">> stop");
            break;
    }   // end switch    
}

}