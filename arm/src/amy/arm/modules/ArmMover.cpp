/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/ArmMover.h"
#include "amy/arm/modules/ArmComputer.h"
#include "amy/arm/modules/JointMover.h"
#include "amy/arm/bus/JointBus.h"
#include "amy/arm/config/ArmConfig.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmMover::logger(Logger::getLogger("amy.arm"));

ArmMover::ArmMover()
{
    benabled = false;
    
    bconnected = false;
    pBus = 0;
}

//ArmMover::~ArmMover()
//{
//}

void ArmMover::init(int timeChange)
{
    // all params must be positive
    if (timeChange <= 0)
        return;

    modName = "ArmMover";
    benabled = true;

    LOG4CXX_INFO(logger, modName << " initialized");      
};

void ArmMover::connect(ArmBus& oBus)
{
    pBus = &oBus;
    bconnected = true;

    LOG4CXX_DEBUG(logger, modName << " connected to bus");      
}

void ArmMover::first()
{
    setState(eSTATE_WAIT);
    setNextState(eSTATE_WAIT);
    
    log4cxx::NDC::push(modName + "-wait");   	
}
                    
// performs a cyclic wave movement of the elbow
void ArmMover::loop()
{
    senseBus();

    if (updateState())
        showState();
    
    oClick.read();
      
    switch (getState())
    {
        case eSTATE_MOVE:
            
            // if move step finished (or first step), get next step and start it
            if (numStep == 0 || oClick.getMillis() > oMoveStep.getTics())
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
       
            oMoveStep.setXmove(JointMover::eMOV_STOP);
            oMoveStep.setYmove(JointMover::eMOV_STOP);
            writeBus();                    
            // after stopping, new wait stage
            setNextState(eSTATE_WAIT);
            break;
    }   // end switch        
}

void ArmMover::senseBus()
{
    if (pBus->getCO_ARMMOVER_START().checkRequested())
    {
        fetchMovement();
        startMovement();        
    }
    
    if (pBus->getCO_ARMMOVER_STOP().checkRequested())
        stopMovement();    
}

// x moves done by horizontal shoulder
// y moves done by elbow
void ArmMover::writeBus()
{    
    // command new move steps to the joints
    int xaction = oMoveStep.getXmove();
    int yaction = oMoveStep.getYmove();
    float vx = oMoveStep.getXspeed();
    float vy = oMoveStep.getYspeed();
    
    JointBus& HSbus = pBus->getJointBus(ArmConfig::horizontal_shoulder);
    JointBus& ELbus = pBus->getJointBus(ArmConfig::elbow);
    
    // command speeds 
    HSbus.getCO_JMOVER_SPEED().request(vx);
    ELbus.getCO_JMOVER_SPEED().request(vy);
    // command actions
    HSbus.getCO_JMOVER_ACTION().request(xaction);
    ELbus.getCO_JMOVER_ACTION().request(yaction);
    
    LOG4CXX_DEBUG(logger, "write bus: xaction = " << xaction << ", yaction = " << yaction);
}

void ArmMover::fetchMovement()
{
    buildMovPajarita();
    
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
            log4cxx::NDC::pop();	          
            log4cxx::NDC::push(modName + "-wait");   	
            break;
                        
        case eSTATE_MOVE:
            LOG4CXX_INFO(logger, ">> move");
            log4cxx::NDC::pop();	          
            log4cxx::NDC::push(modName + "-move");   	
            break;

        case eSTATE_STOP:
            LOG4CXX_INFO(logger, ">> stop");
            log4cxx::NDC::pop();	          
            log4cxx::NDC::push(modName + "-stop");   	
            break;
    }   // end switch    
}



void ArmMover::buildMovPajarita()
{   
    int maxSpeed = 40;    
  
    oMovement.reset();
    oMovement.setMaxSpeed(maxSpeed);

    // step1: move right for 1000 tics
    MoveStep oStep1(0, 1000, maxSpeed);
    // step2: move left for 1000 tics
    MoveStep oStep2(180, 1000, maxSpeed);
    // more steps to complete pajarita
   
    
    oMovement.addMoveStep(oStep1);
    oMovement.addMoveStep(oStep2);
    
    ArmComputer::computeMovement(oMovement);
}


}