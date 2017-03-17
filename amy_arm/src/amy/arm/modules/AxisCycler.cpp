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
            
            // trigger new oscillation
            oOscillator.trigger();
            lastSignal = oOscillator.getSignal();
            
            // go -> GO 
            if (amplitude != 0.0)
                setState(eSTATE_GO);
            // but if zero amplitude requested -> DONE
            else
                setState(eSTATE_DONE);                            

            // show data
            LOG4CXX_INFO(logger, ">> new request");  
            LOG4CXX_INFO(logger, "freq = " << frequency << ", amplitude = " << amplitude);  
            break;  

        case eSTATE_GO:
            // drive arm

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
    }   // end switch    

    if (isStateChanged())
        showState();

    if (bchangeOutput)
        writeBus();        
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
    }   // end switch    
}

}