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
            
    switch (state)
    {
        case eSTATE_START:         
            // launch movement
            
            // trigger new oscillation            
            oTriangularSignal.start();
            xspeed = yspeed = 0.0;
            // if amplitude & frequency defined -> GO 
            if (amplitude != 0.0 && freq != 0.0)
                setState(eSTATE_GO);
            // otherwise, nothing to do -> DONE
            else
                setState(eSTATE_DONE);                            

            // show data
            LOG4CXX_INFO(logger, ">> new request");  
            break;  

        case eSTATE_GO:
            // do cycles

            // perform movement
            updateMovement();
            LOG4CXX_INFO(logger, "speeds: " << oLinearMove.getXSpeed() << ", " << oLinearMove.getYpeed());  
            break;

        case eSTATE_STOP:
            // stop movement

            // command null speeds
            xspeed = yspeed = 0.0;
            // then go to DONE
            setState(eSTATE_DONE);
            break;
    }   // end switch    

    if (isStateChanged())
        showState();

    writeBus();        
}

void FrontalCycler::updateMovSpeed()
{
    // on each period the amplitude must be walked twice
    float avgSpeed = 2.0*amplitude*freq;    
    // the top speed is twice the average speed (for a triangular signal)
    movSpeed = 2.0*avgSpeed;
}

// A square acceleration function is applied
void FrontalCycler::updateMovement()
{
    // modulate speed as a triangular signal
    float speed = movSpeed * oTriangularSignal.sense();    
    // and decompose it in x & y speeds
    oLinearMove.compute(speed);
    xspeed = oLinearMove.getXSpeed();
    yspeed = oLinearMove.getYpeed();
}

void FrontalCycler::senseBus()
{    
    bool bupdateSpeed = false;

    // movement frequency 
    if (pBusFrontalCycler->getCO_CYCLER_FREQ().checkRequested())
    {
        freq = pBusFrontalCycler->getCO_CYCLER_FREQ().getValue();
        oTriangularSignal.setFrequency(freq);
        bupdateSpeed = true;
    }
    // movement amplitude
    if (pBusFrontalCycler->getCO_CYCLER_AMPLITUDE().checkRequested())
    {
        amplitude = pBusFrontalCycler->getCO_CYCLER_AMPLITUDE().getValue();
        bupdateSpeed = true;
    }
    // movement angle
    if (pBusFrontalCycler->getCO_CYCLER_ANGLE().checkRequested())
        oLinearMove.setAngle(pBusFrontalCycler->getCO_CYCLER_ANGLE().getValue());

    // if movement changed, recompute speed
    if (bupdateSpeed)
        updateMovSpeed();
    
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