/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include "log4cxx/ndc.h"

#include "amy/arm/modules/ArmMover.h"
#include "amy/arm/modules/ArmPlanner.h"
#include "amy/arm/modules/ArmComputer.h"
#include "amy/arm/modules/JointMover2.h"
#include "amy/arm/bus/JointBus.h"


using namespace log4cxx;

namespace amy
{
LoggerPtr ArmMover::logger(Logger::getLogger("amy.arm"));

ArmMover::ArmMover()
{
    modName = "ArmMover";
}

//ArmMover::~ArmMover()
//{
//}

void ArmMover::init(Arm& oArm)
{
    benabled = true;

    LOG4CXX_INFO(logger, modName << " initialized");      
};


void ArmMover::first()
{
    setState(eSTATE_WAIT);
    setNextState(eSTATE_WAIT);
    
    log4cxx::NDC::push(modName);   	
}
                    
// performs a cyclic wave movement of the elbow
void ArmMover::loop()
{
    int tics;
    
    senseBus();

    if (updateState())
        showState();
    
    oClick.read();
      
    switch (getState())
    {
        case eSTATE_MOVE:
            
            // 1 second for step endings
            tics = oMoveStep.isStepEnding() ? 1000 : oMoveStep.getTics();
            // if move step finished (or first step), get next step and start it
            if (numStep == 0 || oClick.getMillis() > tics)
            {
                if (newStep())
                {
                    writeBus();                    
                    oClick.start();
                }
                // if movement finished,stop
                else
                    setNextState(eSTATE_STOP);
            }
            break;
                        
        case eSTATE_STOP:
       
//            oMoveStep.setXmove(JointMover::eMOV_STOP);
//            oMoveStep.setYmove(JointMover::eMOV_STOP);
//            writeBus();                    
            // after stopping, new wait stage
            setNextState(eSTATE_WAIT);
            break;
    }   // end switch        
}

void ArmMover::senseBus()
{
    if (pArmBus->getCO_ARMMOVER_START().checkRequested())
    {
        fetchMovement();
        startMovement();        
    }
    
    if (pArmBus->getCO_ARMMOVER_STOP().checkRequested())
        stopMovement();    
}

// x moves done by horizontal shoulder
// y moves done by elbow
void ArmMover::writeBus()
{    
    // command new move steps to the joints
    int xaction = oMoveStep.getXmove();
    int yaction = oMoveStep.getYmove();
    float vx = fabs(oMoveStep.getXspeed());
    float vy = fabs(oMoveStep.getYspeed());
    
    JointBus& oBusHS = pArmBus->getBusHS();
    JointBus& oBusEL = pArmBus->getBusEL();

    // if not step ending, send cruise speeds
    if (!oMoveStep.isStepEnding())
    {
        // command speeds 
//        oBusHS.getCO_JMOVER_SPEED().request(vx);
//        oBusEL.getCO_JMOVER_SPEED().request(vy);
    }
    // command actions
//    oBusHS.getCO_JMOVER_ACTION().request(xaction);
//    oBusEL.getCO_JMOVER_ACTION().request(yaction);
}

void ArmMover::fetchMovement()
{
    ArmPlanner::buildPajaritaMovement(oMovement);
    
    ArmComputer::computeMovement(oMovement);    
}

void ArmMover::startMovement()
{
    // get first move step & jump to MOVE
    numStep = 0;
    setNextState(eSTATE_MOVE);
}

void ArmMover::stopMovement()
{    
    // stop the movement now
    setNextState(eSTATE_STOP);
}

bool ArmMover::newStep()
{
    numStep++;
    // if more steps available, fetch next
    if (numStep <= oMovement.getListMoveSteps().size())
    {
        oMoveStep = oMovement.getListMoveSteps().at(numStep-1);
        LOG4CXX_INFO(logger, "new step: " << oMoveStep.getDescription());
        return true;
    }
    // no more steps available
    else 
        return false;
}

void ArmMover::showState()
{
    switch (getState())
    {
        case eSTATE_WAIT:
            LOG4CXX_INFO(logger, ">> wait");
            break;
                        
        case eSTATE_MOVE:
            LOG4CXX_INFO(logger, ">> move");
            break;

        case eSTATE_STOP:
            LOG4CXX_INFO(logger, ">> stop");
            break;
    }   // end switch    
}


}