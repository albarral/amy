/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/FrontalCycler2.h"
#include "maty/moves/CyclicMath.h"

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
            if (oCyclicMove1.getAmp() != 0.0 || oCyclicMove2.getAmp() != 0.0)
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
    // COMPONENT 1 ...    
    bool bchanged1 = false;
    // frequency 
    if (pBusFrontalCycler->getCO_CYCLER_FREQ1().checkRequested())
    {
        oCyclicMove1.setFreq(pBusFrontalCycler->getCO_CYCLER_FREQ1().getValue());
        bchanged1 = true;
    }
    // amplitude 
    if (pBusFrontalCycler->getCO_CYCLER_AMP1().checkRequested())
    {
        oCyclicMove1.setAmp(pBusFrontalCycler->getCO_CYCLER_AMP1().getValue());
        bchanged1 = true;
    }
    // angle 
    if (pBusFrontalCycler->getCO_CYCLER_ANGLE1().checkRequested())
    {
        oCyclicMove1.setAngle(pBusFrontalCycler->getCO_CYCLER_ANGLE1().getValue());
        bchanged1 = true;
    }
    // phase
    if (pBusFrontalCycler->getCO_CYCLER_PHASE1().checkRequested())
    {
        oCyclicMove1.setPhase(pBusFrontalCycler->getCO_CYCLER_PHASE1().getValue());
        bchanged1 = true;
    }
    
    // COMPONENT 2 ...    
    bool bchanged2 = false;
    // frequency 
    if (pBusFrontalCycler->getCO_CYCLER_FREQ2().checkRequested())
    {
        oCyclicMove2.setFreq(pBusFrontalCycler->getCO_CYCLER_FREQ2().getValue());
        bchanged2 = true;
    }
    // amplitude 
    if (pBusFrontalCycler->getCO_CYCLER_AMP2().checkRequested())
    {
        oCyclicMove2.setAmp(pBusFrontalCycler->getCO_CYCLER_AMP2().getValue());
        bchanged2 = true;
    }
    // angle 
    if (pBusFrontalCycler->getCO_CYCLER_ANGLE2().checkRequested())
    {
        oCyclicMove2.setAngle(pBusFrontalCycler->getCO_CYCLER_ANGLE2().getValue());
        bchanged2 = true;
    }
    // phase
    if (pBusFrontalCycler->getCO_CYCLER_PHASE2().checkRequested())
    {
        oCyclicMove2.setPhase(pBusFrontalCycler->getCO_CYCLER_PHASE2().getValue());
        bchanged2 = true;
    }
    
    if (bchanged1)
    {
        float maxSpeed1 = maty::CyclicMath::getTriangularSpeed4Movement(oCyclicMove1.getFreq(), oCyclicMove1.getAmp());
        oDualOscillator.setPrimaryFreq(oCyclicMove1.getFreq());
        oDualOscillator.setPrimaryAmp(maxSpeed1);        
        oDualOscillator.setPrimaryAngle(oCyclicMove1.getAngle());
        oDualOscillator.setPrimaryPhase(oCyclicMove1.getPhase());
    }
    
    if (bchanged2)
    {
        float maxSpeed2 = maty::CyclicMath::getTriangularSpeed4Movement(oCyclicMove2.getFreq(), oCyclicMove2.getAmp());
        oDualOscillator.setSecondaryFreq(oCyclicMove2.getFreq());
        oDualOscillator.setSecondaryAmp(maxSpeed2);        
        oDualOscillator.setSecondaryAngle(oCyclicMove2.getAngle());
        oDualOscillator.setSecondaryPhase(oCyclicMove2.getPhase());
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