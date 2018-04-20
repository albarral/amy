/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/ArmCycler.h"
#include "tron/signals/CyclicMath.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmCycler::logger(Logger::getLogger("amy.arm"));

ArmCycler::ArmCycler()
{
    modName = "ArmCycler";
    pCyclerBus = 0;
    pPanBus = 0;
    pTiltBus = 0;
    // control priority
    priority = 1; 
}

void ArmCycler::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}

void ArmCycler::first()
{
    // start at done
    setState(eSTATE_DONE);
    
    pCyclerBus = &pArmBus->getCyclerBus1();
    pPanBus = &pArmBus->getPanBus();
    pTiltBus = &pArmBus->getTiltBus();
    log4cxx::NDC::push(modName);   	
}
                    
void ArmCycler::loop()
{    
    senseBus();

    int state = getState();
    // skip if DONE 
    if (state == eSTATE_DONE)            
        return;

    if (getStable() == 0)
        showState();
    
    switch (state)
    {
        case eSTATE_START:         
            
            // if some amplitude defined -> GO 
            if (oCyclicComponent1.getAmp() != 0.0 || oCyclicComponent2.getAmp() != 0.0)
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
void ArmCycler::triggerMove()
{
    // trigger new oscillation 
    oDualOscillator.reset();
    xspeed = yspeed = 0.0;

    // show oscillator data
    LOG4CXX_INFO(logger, oDualOscillator.toString());  
}

// update the cyclic movement
void ArmCycler::updateMove()
{
    // update oscillator
    oDualOscillator.update();
    // and combine them
    xspeed =  oDualOscillator.getX();
    yspeed =  oDualOscillator.getY();
}

// stop the cyclic movement
void ArmCycler::stopMove()
{
    // command null speeds
    xspeed = yspeed = 0.0;
}

void ArmCycler::senseBus()
{  
    // COMPONENT 1 ...    
    bool bchanged1 = false;
    // frequency 
    if (pCyclerBus->getCO_CYCLER_FREQ1().checkRequested())
    {
        oCyclicComponent1.setFreq(pCyclerBus->getCO_CYCLER_FREQ1().getValue());
        bchanged1 = true;
    }
    // amplitude 
    if (pCyclerBus->getCO_CYCLER_AMP1().checkRequested())
    {
        oCyclicComponent1.setAmp(pCyclerBus->getCO_CYCLER_AMP1().getValue());
        bchanged1 = true;
    }
    // angle 
    if (pCyclerBus->getCO_CYCLER_ANGLE1().checkRequested())
    {
        oCyclicComponent1.setAngle(pCyclerBus->getCO_CYCLER_ANGLE1().getValue());
        bchanged1 = true;
    }
    // phase
    if (pCyclerBus->getCO_CYCLER_PHASE1().checkRequested())
    {
        oCyclicComponent1.setPhase(pCyclerBus->getCO_CYCLER_PHASE1().getValue());
        bchanged1 = true;
    }
    
    // COMPONENT 2 ...    
    bool bchanged2 = false;
    // frequency 
    if (pCyclerBus->getCO_CYCLER_FREQ2().checkRequested())
    {
        oCyclicComponent2.setFreq(pCyclerBus->getCO_CYCLER_FREQ2().getValue());
        bchanged2 = true;
    }
    // amplitude 
    if (pCyclerBus->getCO_CYCLER_AMP2().checkRequested())
    {
        oCyclicComponent2.setAmp(pCyclerBus->getCO_CYCLER_AMP2().getValue());
        bchanged2 = true;
    }
    // angle 
    if (pCyclerBus->getCO_CYCLER_ANGLE2().checkRequested())
    {
        oCyclicComponent2.setAngle(pCyclerBus->getCO_CYCLER_ANGLE2().getValue());
        bchanged2 = true;
    }
    // phase
    if (pCyclerBus->getCO_CYCLER_PHASE2().checkRequested())
    {
        oCyclicComponent2.setPhase(pCyclerBus->getCO_CYCLER_PHASE2().getValue());
        bchanged2 = true;
    }
    
    if (bchanged1)
    {
        float maxSpeed1 = tron::CyclicMath::getTriangularSpeed4Movement(oCyclicComponent1.getFreq(), oCyclicComponent1.getAmp());
        oDualOscillator.setPrimaryFreq(oCyclicComponent1.getFreq());
        oDualOscillator.setPrimaryAmp(maxSpeed1);        
        oDualOscillator.setPrimaryAngle(oCyclicComponent1.getAngle());
        oDualOscillator.setPrimaryPhase(oCyclicComponent1.getPhase());
    }
    
    if (bchanged2)
    {
        float maxSpeed2 = tron::CyclicMath::getTriangularSpeed4Movement(oCyclicComponent2.getFreq(), oCyclicComponent2.getAmp());
        oDualOscillator.setSecondaryFreq(oCyclicComponent2.getFreq());
        oDualOscillator.setSecondaryAmp(maxSpeed2);        
        oDualOscillator.setSecondaryAngle(oCyclicComponent2.getAngle());
        oDualOscillator.setSecondaryPhase(oCyclicComponent2.getPhase());
    }

    // action requested 
    if (pCyclerBus->getCO_CYCLER_ACTION().checkRequested())
    {
        // start requested
        if (pCyclerBus->getCO_CYCLER_ACTION().getValue()) 
            setState(eSTATE_START);                   
        // stop requested
        else
            setState(eSTATE_STOP);                   
    }
}

void ArmCycler::writeBus()
{  
    // control pan & tilt speeds
    pPanBus->getCO_AXIS_SPEED2().request(xspeed, priority);
    pTiltBus->getCO_AXIS_SPEED2().request(yspeed, priority);
}


void ArmCycler::showState()
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