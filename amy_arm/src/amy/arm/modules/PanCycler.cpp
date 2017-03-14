/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include "log4cxx/ndc.h"

#include "amy/arm/modules/PanCycler.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr PanCycler::logger(Logger::getLogger("amy.arm"));

PanCycler::PanCycler()
{
    modName = "PanCycler";
    // control priority
    priority = 1; //oArmConfig.getPriority4PanCyclers();
}

void PanCycler::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}

void PanCycler::first()
{
    // start at done
    setState(eSTATE_DONE);

    log4cxx::NDC::push(modName);   	
}
                    
void PanCycler::loop()
{
    // TEMP flag (to avoid sending pan speed on every loop)
    bool bsendSpeed = false;
    
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
            LOG4CXX_INFO(logger, "freq = " << 1.0/period << ", amplitude = " << amplitude);  
            break;  

        case eSTATE_GO:
            // drive arm

            // get oscillator signal
            signal = oOscillator.run();           
            // if signal sign changed, change out speed
            if (signal*lastSignal <= 0)
            {
                panSpeed = (signal > 0 ? cruiseSpeed : -cruiseSpeed);
                bsendSpeed = true;
                LOG4CXX_INFO(logger, " panSpeed=" + std::to_string(panSpeed));
            }        
            // store signal
            lastSignal = signal;
            break;
    }   // end switch    

    if (isStateChanged())
        showState();

    if (bsendSpeed)
        writeBus();        
}


void PanCycler::senseBus()
{    
    if (pArmBus->getCO_PAN_FREQ().checkRequested())
    {
        float freq = pArmBus->getCO_PAN_FREQ().getValue();
        if (freq != 0.0)
        {
            oOscillator.setFrequency(freq);
            period = 1.0/freq;
            updateCruiseSpeed();
        }
    }

    if (pArmBus->getCO_PAN_AMPLITUDE().checkRequested())
    {
        amplitude = pArmBus->getCO_PAN_AMPLITUDE().getValue();
        updateCruiseSpeed();
    }
    
    if (pArmBus->getCO_PAN_TRIGGER().checkRequested())
        setState(eSTATE_START);                   

    if (pArmBus->getCO_PAN_STOP().checkRequested())
    {
        oOscillator.stop();
        setState(eSTATE_DONE);                   
    }
}

void PanCycler::writeBus()
{  
    // control pan speed
    pArmBus->getCO_PAN_SPEED().request(panSpeed, priority);
}

void PanCycler::updateCruiseSpeed()
{
    // speed for the cyclic movement: the amplitude must be walked twice on each period
    cruiseSpeed = 2*fabs(amplitude) / period;    
}

void PanCycler::showState()
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