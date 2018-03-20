/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/FrontalCycler2.h"
#include "amy/arm/move/CyclicMove.h"

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
    amplitude1 = amplitude2 = 0.0;
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
            if (oDualOscillator.getPrimaryAmp() != 0.0)
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
        oDualOscillator.setPrimaryFreq(pBusFrontalCycler->getCO_CYCLER_FREQ1().getValue());
        float maxSpeed1 = CyclicMove::getTriangularSpeed4Movement(oDualOscillator.getPrimaryFreq(), amplitude1);
        oDualOscillator.setPrimaryAmp(maxSpeed1);
    }
    // amplitude 
    if (pBusFrontalCycler->getCO_CYCLER_AMP1().checkRequested())
    {
        amplitude1 = pBusFrontalCycler->getCO_CYCLER_AMP1().getValue();
        float maxSpeed1 = CyclicMove::getTriangularSpeed4Movement(oDualOscillator.getPrimaryFreq(), amplitude1);
        oDualOscillator.setPrimaryAmp(maxSpeed1);
    }
    // angle 
    if (pBusFrontalCycler->getCO_CYCLER_ANGLE1().checkRequested())
        oDualOscillator.setPrimaryAngle(pBusFrontalCycler->getCO_CYCLER_ANGLE1().getValue());
    // phase
    if (pBusFrontalCycler->getCO_CYCLER_PHASE1().checkRequested())
        oDualOscillator.setPrimaryPhase(pBusFrontalCycler->getCO_CYCLER_PHASE1().getValue());
    
    // component 2 ...
    // frequency
    if (pBusFrontalCycler->getCO_CYCLER_FREQ2().checkRequested())
    {
        oDualOscillator.setSecondaryFreq(pBusFrontalCycler->getCO_CYCLER_FREQ2().getValue());
        float maxSpeed2 = CyclicMove::getTriangularSpeed4Movement(oDualOscillator.getSecondaryFreq(), amplitude2);
        oDualOscillator.setSecondaryAmp(maxSpeed2);
    }
    // amplitude
    if (pBusFrontalCycler->getCO_CYCLER_AMP2().checkRequested())
    {
        amplitude2 = pBusFrontalCycler->getCO_CYCLER_AMP2().getValue();
        float maxSpeed2 = CyclicMove::getTriangularSpeed4Movement(oDualOscillator.getSecondaryFreq(), amplitude2);
        oDualOscillator.setSecondaryAmp(maxSpeed2);
    }
    // angle 
    if (pBusFrontalCycler->getCO_CYCLER_ANGLE2().checkRequested())
        oDualOscillator.setSecondaryAngle(pBusFrontalCycler->getCO_CYCLER_ANGLE2().getValue());
    // phase
    if (pBusFrontalCycler->getCO_CYCLER_PHASE2().checkRequested())
        oDualOscillator.setSecondaryPhase(pBusFrontalCycler->getCO_CYCLER_PHASE2().getValue());
    

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