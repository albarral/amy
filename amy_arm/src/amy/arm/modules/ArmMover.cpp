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
    barmed = false;
    factor = 1.1;   // default change factor (10%) 
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
    log4cxx::NDC::push(modName);   	
}
                    
// performs a cyclic wave movement of the elbow
void ArmMover::loop()
{
    senseBus();
    
    int state = getState();    
    if (isStateChanged())
        showState();
    
    // skip if WAIT 
    if (state == eSTATE_WAIT)            
        return;

    switch (state)
    {
        case eSTATE_TALK:
            
            // go to WAIT    
            setState(eSTATE_WAIT);
            break;
    }   // end switch        
    
    writeBus();
}

void ArmMover::senseBus()
{
    bool bupdateMove = false;

    // check movement type requests
    if (pArmBus->getCO_MOVER_TYPE().checkRequested())
    {
        // compute movement & set to armed
        oCyclicMove = oMoveFactory.computeMove(pArmBus->getCO_MOVER_TYPE().getValue());
        barmed = true;
        bupdateMove = true;
    }
    
    // check action requests
    if (pArmBus->getCO_MOVER_ACTION().checkRequested())
    {                
        // store requested action
        bcyclerAction = pBusFrontalCycler->getCO_CYCLER_ACTION().getValue();
        bupdateMove = true;
    }
    
    // check turn requests
    if (pArmBus->getCO_MOVER_TURN().checkRequested())
    {                
        // update movement orientation
        int angle = pArmBus->getCO_MOVER_TURN().getValue();
        oCyclicMove.makeTurn(angle);
        bupdateMove = true;
    }
        
    // check width requests
    if (pArmBus->getCO_MOVER_WIDER().checkRequested())
    {                
        // make move wider
        if (pArmBus->getCO_MOVER_WIDER().getValue())
            oCyclicMove.makeWider(factor);
        // make move narrower
        else
            oCyclicMove.makeWider(1.0/factor);
        bupdateMove = true;
    }
        
    // check height requests
    if (pArmBus->getCO_MOVER_TALLER().checkRequested())
    {                
        // make move taller
        if (pArmBus->getCO_MOVER_TALLER().getValue())
            oCyclicMove.makeTaller(factor);
        // make move shorter
        else
            oCyclicMove.makeTaller(1.0/factor);
        bupdateMove = true;
    }
           
    // check speed requests
    if (pArmBus->getCO_MOVER_FASTER().checkRequested())
    {                
        // make move faster
        if (pArmBus->getCO_MOVER_FASTER().getValue())
            oCyclicMove.makeFaster(factor);
        // make move slower
        else
            oCyclicMove.makeFaster(1.0/factor);
        bupdateMove = true;
    }

    // movement to be updated -> go to TALK    
    if (barmed && bupdateMove)
        setState(eSTATE_TALK);                       
}

void ArmMover::writeBus()
{    
    // command new move steps to the joints
    pBusFrontalCycler->getCO_CYCLER_FREQ().request(oCyclicMove.getFreq1());     
    pBusFrontalCycler->getCO_CYCLER_ANGLE().request(oCyclicMove.getAngle1());
    pBusFrontalCycler->getCO_CYCLER_AMPLITUDE().request(oCyclicMove.getAmp1());
    pBusFrontalCycler->getCO_CYCLER_ACTION().request(bcyclerAction);
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