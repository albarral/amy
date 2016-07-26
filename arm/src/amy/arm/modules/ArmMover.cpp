/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/ArmMover.h"
#include "amy/arm/modules/JointMover.h"

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
    this->timeChange = timeChange;
    jointName = "elbow";    
    benabled = true;

    LOG4CXX_INFO(logger, modName << " initialized");      
    LOG4CXX_INFO(logger, "tchange=" << timeChange);      
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
        case eSTATE_RIGHT:
            
            // if right period passed
            if (oClick.getMillis() > timeChange)
            {
                // turn left
                writeBus(JointMover::eMOV_NEGATIVE);
                prevState = eSTATE_RIGHT;
                setNextState(eSTATE_CHANGE);
            }
            break;
            
        case eSTATE_CHANGE:
            
            if (prevState == eSTATE_RIGHT && realSpeed < 0)
            {
                setNextState(eSTATE_LEFT);
                oClick.start();
            }
            else if (prevState == eSTATE_LEFT && realSpeed > 0)
            {
                setNextState(eSTATE_RIGHT);
                oClick.start();
            }

            break;
                    
        case eSTATE_LEFT:
            
            // if left period passed
            if (oClick.getMillis() > timeChange)
            {
                // turn right
                writeBus(JointMover::eMOV_POSITIVE);
                prevState = eSTATE_LEFT;
                setNextState(eSTATE_CHANGE);
            }
            break;
            
        case eSTATE_STOP:

            if (realSpeed != 0)
                writeBus(JointMover::eMOV_STOP);
            // after stopping, new wait stage
            setNextState(eSTATE_WAIT);
            break;
    }   // end switch        
}

void ArmMover::senseBus()
{
    realSpeed = pBus->getJointBus(jointName).getSO_REAL_SPEED().getValue();
    
    if (pBus->getCO_ARMMOVER_START().checkRequested())
        start();
    
    if (pBus->getCO_ARMMOVER_STOP().checkRequested())
        stop();    
}

void ArmMover::writeBus(int command)
{
    pBus->getJointBus(jointName).getCO_JMOVER_ACTION().request(command);
    
    LOG4CXX_DEBUG(logger, "command = " << command);
}

void ArmMover::start()
{
    setNextState(eSTATE_RIGHT);
    oClick.start();
}

void ArmMover::stop()
{
    setNextState(eSTATE_STOP);
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
            
        case eSTATE_RIGHT:
            LOG4CXX_INFO(logger, ">> right");
            log4cxx::NDC::pop();	          
            log4cxx::NDC::push(modName + "-right");   	
            break;
            
        case eSTATE_CHANGE:
            LOG4CXX_INFO(logger, ">> change");
            log4cxx::NDC::pop();	          
            log4cxx::NDC::push(modName + "-change");   	
            break;
            
        case eSTATE_LEFT:
            LOG4CXX_INFO(logger, ">> left");
            log4cxx::NDC::pop();	          
            log4cxx::NDC::push(modName + "-left");   	
            break;

        case eSTATE_STOP:
            LOG4CXX_INFO(logger, ">> stop");
            log4cxx::NDC::pop();	          
            log4cxx::NDC::push(modName + "-stop");   	
            break;
    }   // end switch    
}

}