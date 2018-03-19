/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/FrontalCycler2.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr FrontalCycler2::logger(Logger::getLogger("amy.arm"));

FrontalCycler2::FrontalCycler2()
{
    modName = "FrontalCycler2";
    pBusFrontalCycler = 0;
    pPanBus = 0;
    pTiltBus = 0;
    // control priority
    priority = 1; 
}

void FrontalCycler2::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}

void FrontalCycler2::first()
{
    // start at done
    setState(eSTATE_DONE);
    
    pBusFrontalCycler = &pArmBus->getFrontalCyclerBus();
    pPanBus = &pArmBus->getPanBus();
    pTiltBus = &pArmBus->getTiltBus();
    log4cxx::NDC::push(modName);   	
}
                    
void FrontalCycler2::loop()
{    
    senseBus();

    int state = getState();
    // skip if DONE 
    if (state == eSTATE_DONE)            
        return;

    if (isStateChanged())
        showState();
            
    switch (state)
    {
        case eSTATE_START:         
            
            // if some amplitude defined -> GO 
            if (oDualOscillator.getMainAmp() != 0.0)
            {
                // launch movement    
                triggerMove();
                setState(eSTATE_GO);
            }
            // otherwise, nothing to do -> DONE
            else
                setState(eSTATE_DONE);                            
            break;  

        case eSTATE_GO:

            // perform movement
            updateMove();
            LOG4CXX_INFO(logger, "speeds: " << xspeed << ", " << yspeed);  
            break;

        case eSTATE_STOP:

            // stop movement
            stopMove();
            // then go to DONE
            setState(eSTATE_DONE);
            break;
    }   // end switch    

    writeBus();        
}

// triggers a cyclic movement
void FrontalCycler2::triggerMove()
{
    // trigger new oscillation 
    oDualOscillator.reset();
    xspeed = yspeed = 0.0;

    // show oscillator data
    LOG4CXX_INFO(logger, oDualOscillator.toString());  
}

// update the cyclic movement
void FrontalCycler2::updateMove()
{
    // update oscillator
    oDualOscillator.update();
    // and combine them
    xspeed =  oDualOscillator.getX();
    yspeed =  oDualOscillator.getY();
}

// stop the cyclic movement
void FrontalCycler2::stopMove()
{
    // command null speeds
    xspeed = yspeed = 0.0;
}

void FrontalCycler2::senseBus()
{  
    // component 1 ...    
    // frequency 
    if (pBusFrontalCycler->getCO_CYCLER_FREQ1().checkRequested())
    {
        oDualOscillator.setMainFreq(pBusFrontalCycler->getCO_CYCLER_FREQ1().getValue());
    }
    // amplitude 
    if (pBusFrontalCycler->getCO_CYCLER_AMPLITUDE1().checkRequested())
    {
        oDualOscillator.setMainAmp(pBusFrontalCycler->getCO_CYCLER_AMPLITUDE1().getValue());
    }
    // angle 
    if (pBusFrontalCycler->getCO_CYCLER_ANGLE1().checkRequested())
    {
        oDualOscillator.setMainAngle(pBusFrontalCycler->getCO_CYCLER_ANGLE1().getValue());
    }
    
    // component 2 ...
    // frequency
    if (pBusFrontalCycler->getCO_CYCLER_FREQ2().checkRequested())
    {
        // temp: secondary frequency should be given in relative form
        float freq2 = pBusFrontalCycler->getCO_CYCLER_FREQ2().getValue();
        float freq1 = oDualOscillator.getMainFreq();
        float relFreq = (freq1 != 0.0 ? freq2 / freq1 : 0.0);
        oDualOscillator.setRelativeFreq(relFreq);
    }
    // amplitude
    if (pBusFrontalCycler->getCO_CYCLER_AMPLITUDE2().checkRequested())
    {
        // temp: secondary amplitude should be given in relative form
        float amp2 = pBusFrontalCycler->getCO_CYCLER_AMPLITUDE2().getValue();
        float amp1 = oDualOscillator.getMainAmp();
        float relFactor = (amp1 != 0.0 ? amp2 / amp1 : 0.0);
        oDualOscillator.setRelativeFactor(relFactor);
    }
    // angle (nothing done, dual oscillator is always orthogonal)
    
    // phase between components
    if (pBusFrontalCycler->getCO_CYCLER_PHASE().checkRequested())
    {
        oDualOscillator.setPhaseGap(pBusFrontalCycler->getCO_CYCLER_PHASE().getValue());
    }

    // action requested 
    if (pBusFrontalCycler->getCO_CYCLER_ACTION().checkRequested())
    {
        // start requested
        if (pBusFrontalCycler->getCO_CYCLER_ACTION().getValue()) 
            setState(eSTATE_START);                   
        // stop requested
        else
            setState(eSTATE_STOP);                   
    }
}

void FrontalCycler2::writeBus()
{  
    // control pan & tilt speeds
    pPanBus->getCO_AXIS_SPEED2().request(xspeed, priority);
    pTiltBus->getCO_AXIS_SPEED2().request(yspeed, priority);
}


void FrontalCycler2::showState()
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