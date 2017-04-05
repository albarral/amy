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
    pBusHS = pBusVS = 0;
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

    pBusHS = &pArmBus->getBusHS();
    pBusVS = &pArmBus->getBusVS();
    
    log4cxx::NDC::push(modName);   	
}
                    
void FrontalCycler::loop()
{
    float signal;
    
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
            oOscillator2.reset();
            xaccel = yaccel = 0.0;
            // if amplitude & frequency defined -> GO 
            if (oEllipticMove.getLenA() != 0.0 && oEllipticMove.getFrequency() != 0.0)
                setState(eSTATE_GO);
            // otherwise, nothing to do -> DONE
            else
                setState(eSTATE_DONE);                            

            // show data
            LOG4CXX_INFO(logger, ">> new request");  
            LOG4CXX_INFO(logger, oEllipticMove.toString());  
            break;  

        case eSTATE_GO:
            // do cycles

            // get oscillator signal
            signal = oOscillator2.update();
            LOG4CXX_INFO(logger, "oscillator: " << oOscillator2.getPosition() << ", signal = " << signal);  
            // and perform movement
            doPrimaryMove(signal);
            //doSecondaryMove(signal);
            break;

        case eSTATE_STOP:
            // stop movement

            // stop oscillator and command null accels
            oOscillator2.stop();
            xaccel = yaccel = 0.0;  // better not to command anything
            // then go to DONE
            setState(eSTATE_DONE);
            break;
    }   // end switch    

    if (isStateChanged())
        showState();

    writeBus();        
}

// A square acceleration function is applied
void FrontalCycler::doPrimaryMove(int signal)
{
    int sign;
    switch (signal)
    {
        case 0:
        case 3:
            sign = 1;
            break;
            
        case 1:
        case 2:
            sign = -1;
            break;
            
        default: 
            sign = 0;
    }
    
    xaccel = sign*oEllipticMove.getAccelx1();
    yaccel = sign*oEllipticMove.getAccely1();
    LOG4CXX_INFO(logger, "xaccel =  " << xaccel << ", yaccel = " << yaccel);  
}

void FrontalCycler::doSecondaryMove(int signal)
{
    
}

void FrontalCycler::senseBus()
{    
    bool bupdateMove = false;

    // movement angle
    if (pArmBus->getCO_FRONT_ANGLE().checkRequested())
    {
        oEllipticMove.setAngle(pArmBus->getCO_FRONT_ANGLE().getValue());
        bupdateMove = true;
    }
    // mayor axis
    if (pArmBus->getCO_FRONT_MAYOR().checkRequested())
    {
        oEllipticMove.setLengthA(pArmBus->getCO_FRONT_MAYOR().getValue());
        bupdateMove = true;
    }
    // minor axis
    if (pArmBus->getCO_FRONT_MINOR().checkRequested())
    {
        oEllipticMove.setLengthB(pArmBus->getCO_FRONT_MINOR().getValue());
        bupdateMove = true;
    }    
    // movement frequency 
    if (pArmBus->getCO_FRONT_FREQ().checkRequested())
    {
        float freq = pArmBus->getCO_FRONT_FREQ().getValue();
        oEllipticMove.setFrequency(freq);
        oOscillator2.setFrequency(freq);
        bupdateMove = true;
    }

    // if some movement parameter changed, recompute movement
    if (bupdateMove)
        oEllipticMove.compute();
    
    // action requested 
    if (pArmBus->getCO_FRONT_ACTION().checkRequested())
    {
        // start requested
        if (pArmBus->getCO_FRONT_ACTION().getValue()) 
            setState(eSTATE_START);                   
        // stop requested
        else
            setState(eSTATE_STOP);                   
    }
}

void FrontalCycler::writeBus()
{  
    // control HS and VS joints
    pBusHS->getCO_JOINT_ACCEL().request(xaccel, priority);
    pBusVS->getCO_JOINT_ACCEL().request(yaccel, priority);
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