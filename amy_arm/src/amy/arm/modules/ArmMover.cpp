/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/ArmMover.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmMover::logger(Logger::getLogger("amy.arm"));

ArmMover::ArmMover()
{
    modName = "ArmMover";
    // bus
    pBusFrontalCycler = 0;
    pBusFrontalCycler2 = 0;
}

//ArmMover::~ArmMover()
//{
//}

void ArmMover::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}


void ArmMover::first()
{
    // start at WAIT
    setState(eSTATE_WAIT);
    
    pBusFrontalCycler = &pArmBus->getFrontalCyclerBus();    
    //pBusFrontalCycler2 = &pArmBus->getFrontalCyclerBus2();    // to do (when second cycler available)
    log4cxx::NDC::push(modName);   	
}
                    
// performs a cyclic wave movement of the elbow
void ArmMover::loop()
{
    senseBus();
    
    // skip if WAIT 
    if (getState() == eSTATE_WAIT)            
        return;

    if (isStateChanged())
        showState();

    switch (getState())
    {
        case eSTATE_TALK:
            
            // send commands to cyclers & go to WAIT    
            talk2Cyclers();
            setState(eSTATE_WAIT);
            break;
    }   // end switch        
    
    //writeBus();
}

void ArmMover::senseBus()
{
    // check move requests
    if (pArmBus->getCO_MOVER_TYPE().checkRequested())
    {
        // compute movement 
        oCyclicMove = oMoveFactory.computeMove(pArmBus->getCO_MOVER_TYPE().getValue());
        // and give it an elasticity to change
        oCyclicMove.setElasticity(0.1);
        // prepare to send a trigger message
        message = eMSG_TRIGGER;
        setState(eSTATE_TALK);                       
    }
    
    // check action requests
    if (pArmBus->getCO_MOVER_ACTION().checkRequested())
    {                
        // prepare to send a trigger or stop message
        if (pArmBus->getCO_MOVER_ACTION().getValue())
            message = eMSG_TRIGGER;
        else
            message = eMSG_STOP;
        setState(eSTATE_TALK);                       
    }
    
    // check turn requests
    if (pArmBus->getCO_MOVER_TURN().checkRequested())
    {                
        // update movement orientation
        oCyclicMove.makeTurn(pArmBus->getCO_MOVER_TURN().getValue());
        // prepare to send an update message
        message = eMSG_UPDATE;
        setState(eSTATE_TALK);                       
    }
        
    // check width requests
    if (pArmBus->getCO_MOVER_WIDER().checkRequested())
    {                
        // make move wider or narrower
        oCyclicMove.makeWider(pArmBus->getCO_MOVER_WIDER().getValue());
        // prepare to send an update message
        message = eMSG_UPDATE;
        setState(eSTATE_TALK);                       
    }
        
    // check height requests
    if (pArmBus->getCO_MOVER_TALLER().checkRequested())
    {                
        // make move taller or shorter
        oCyclicMove.makeTaller(pArmBus->getCO_MOVER_TALLER().getValue());
        // prepare to send an update message
        message = eMSG_UPDATE;
        setState(eSTATE_TALK);                       
    }
           
    // check speed requests
    if (pArmBus->getCO_MOVER_FASTER().checkRequested())
    {                
        // make move faster or slower
        oCyclicMove.makeFaster(pArmBus->getCO_MOVER_FASTER().getValue());
        // prepare to send an update message
        message = eMSG_UPDATE;
        setState(eSTATE_TALK);                       
    }
}

void ArmMover::talk2Cyclers()
{
    switch (message)
    {
        case eMSG_TRIGGER:
            // triggers the cyclic movement
            triggerMove();
            break;
            
        case eMSG_STOP:
            // stops the cyclic movement
            stopMove();
            break;
            
        case eMSG_UPDATE:            
            // changes the cyclic movement           
            updateMove();
            break;
    }
}

void ArmMover::triggerMove()
{    
    // modulates both cyclic movements           
    updateMove();
    // starts move of first cycler
    if (pBusFrontalCycler != 0)
        pBusFrontalCycler->getCO_CYCLER_ACTION().request(true);
    // starts move of second cycler
    if (pBusFrontalCycler2 != 0)
        pBusFrontalCycler2->getCO_CYCLER_ACTION().request(true);
}

void ArmMover::stopMove()
{    
    // stops move of first cycler
    if (pBusFrontalCycler != 0)
        pBusFrontalCycler->getCO_CYCLER_ACTION().request(false);
    // stops move of second cycler
    if (pBusFrontalCycler2 != 0)
        pBusFrontalCycler2->getCO_CYCLER_ACTION().request(false);
}

void ArmMover::updateMove()
{        
    // modulates move of first cycler
    if (pBusFrontalCycler != 0)
    {
        pBusFrontalCycler->getCO_CYCLER_FREQ().request(oCyclicMove.getFreq1());     
        pBusFrontalCycler->getCO_CYCLER_ANGLE().request(oCyclicMove.getAngle1());
        pBusFrontalCycler->getCO_CYCLER_AMPLITUDE().request(oCyclicMove.getAmp1());
    }
    // modulates move of second cycler
    if (pBusFrontalCycler2 != 0)
    {
        pBusFrontalCycler2->getCO_CYCLER_FREQ().request(oCyclicMove.getFreq2());     
        pBusFrontalCycler2->getCO_CYCLER_ANGLE().request(oCyclicMove.getAngle2());
        pBusFrontalCycler2->getCO_CYCLER_AMPLITUDE().request(oCyclicMove.getAmp2());
    }
}

void ArmMover::writeBus()
{
    // nothing to do here    
    // control already done by triggerMove, stopMove & updateMove methods
}

void ArmMover::showState()
{
    switch (getState())
    {
        case eSTATE_WAIT:
            LOG4CXX_INFO(logger, ">> wait");
            break;
                        
        case eSTATE_TALK:
            LOG4CXX_INFO(logger, ">> talk");
            break;
    }   // end switch    
}


}