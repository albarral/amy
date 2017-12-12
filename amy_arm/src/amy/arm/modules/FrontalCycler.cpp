/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/FrontalCycler.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr FrontalCycler::logger(Logger::getLogger("amy.arm"));

FrontalCycler::FrontalCycler()
{
    modName = "FrontalCycler";
    pBusFrontalCycler = 0;
    pPanBus = 0;
    pTiltBus = 0;
    oClock.setFrequency(50);
    // control priority
    priority = 1; 
}

void FrontalCycler::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}

void FrontalCycler::first()
{
    // start at done
    setState(eSTATE_DONE);
    
    pBusFrontalCycler = &pArmBus->getFrontalCyclerBus();
    pPanBus = &pArmBus->getPanBus();
    pTiltBus = &pArmBus->getTiltBus();
    log4cxx::NDC::push(modName);   	
}
                    
void FrontalCycler::loop()
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
            if (oLinearCycler1.getAmp() != 0.0 || oLinearCycler2.getAmp() != 0.0)
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
            LOG4CXX_DEBUG(logger, "speeds1: " << oLinearCycler1.getXSpeed() << ", " << oLinearCycler1.getYSpeed());  
            LOG4CXX_DEBUG(logger, "speeds2: " << oLinearCycler2.getXSpeed() << ", " << oLinearCycler2.getYSpeed());  
            //LOG4CXX_INFO(logger, "speeds: " << xspeed << ", " << yspeed);  
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
void FrontalCycler::triggerMove()
{
    // trigger new oscillation 
    oClock.reset();
    oLinearCycler1.trigger(oClock);
    oLinearCycler2.trigger(oClock);
    xspeed = yspeed = 0.0;

    // show cyclers data
    LOG4CXX_INFO(logger, "cycler 1 - " << oLinearCycler1.toString());  
    LOG4CXX_INFO(logger, "cycler 2 - " << oLinearCycler2.toString());  
}

// update the cyclic movement
void FrontalCycler::updateMove()
{
    // update movement components
    oClock.update();
    oLinearCycler1.update(oClock);
    oLinearCycler2.update(oClock);
    // and combine them
    xspeed =  oLinearCycler1.getXSpeed() + oLinearCycler2.getXSpeed();
    yspeed =  oLinearCycler1.getYSpeed() + oLinearCycler2.getYSpeed();
}

// stop the cyclic movement
void FrontalCycler::stopMove()
{
    // command null speeds
    xspeed = yspeed = 0.0;
}

void FrontalCycler::senseBus()
{  
    // component 1 ...    
    // frequency 
    if (pBusFrontalCycler->getCO_CYCLER_FREQ1().checkRequested())
    {
        oLinearCycler1.setFreq(pBusFrontalCycler->getCO_CYCLER_FREQ1().getValue());
    }
    // amplitude 
    if (pBusFrontalCycler->getCO_CYCLER_AMPLITUDE1().checkRequested())
    {
        oLinearCycler1.setAmp(pBusFrontalCycler->getCO_CYCLER_AMPLITUDE1().getValue());
    }
    // angle 
    if (pBusFrontalCycler->getCO_CYCLER_ANGLE1().checkRequested())
    {
        oLinearCycler1.setAngle(pBusFrontalCycler->getCO_CYCLER_ANGLE1().getValue());
    }
    
    // component 2 ...
    // frequency
    if (pBusFrontalCycler->getCO_CYCLER_FREQ2().checkRequested())
    {
        oLinearCycler2.setFreq(pBusFrontalCycler->getCO_CYCLER_FREQ2().getValue());
    }
    // amplitude
    if (pBusFrontalCycler->getCO_CYCLER_AMPLITUDE2().checkRequested())
    {
        oLinearCycler2.setAmp(pBusFrontalCycler->getCO_CYCLER_AMPLITUDE2().getValue());
    }
    // angle
    if (pBusFrontalCycler->getCO_CYCLER_ANGLE2().checkRequested())
    {
        oLinearCycler2.setAngle(pBusFrontalCycler->getCO_CYCLER_ANGLE2().getValue());
    }
    
    // phase between components
    if (pBusFrontalCycler->getCO_CYCLER_PHASE().checkRequested())
    {
        oLinearCycler2.setPhase(pBusFrontalCycler->getCO_CYCLER_PHASE().getValue());
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

void FrontalCycler::writeBus()
{  
    // control pan & tilt speeds
    pPanBus->getCO_AXIS_SPEED2().request(xspeed, priority);
    pTiltBus->getCO_AXIS_SPEED2().request(yspeed, priority);
}


void FrontalCycler::showState()
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