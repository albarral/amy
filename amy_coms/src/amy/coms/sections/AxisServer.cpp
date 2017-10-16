/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/sections/AxisServer.h"
#include "talky/topics/ArmTopic.h"


namespace amy
{
log4cxx::LoggerPtr AxisServer::logger(log4cxx::Logger::getLogger("amy.coms"));

AxisServer::AxisServer()
{    
    pArmInterface = 0;
}

void AxisServer::connect2Arm(iArmInterface& oArmInterface)
{
    pArmInterface = &oArmInterface;
}

bool AxisServer::processCommand(talky::Command& oCommand)
{
    bool bret = true;
    float quantity = oCommand.getQuantity();
    
    switch (oCommand.getConcept())
    {
        case talky::ArmTopic::eAXIS_PAN_POS:
            LOG4CXX_INFO(logger, "> move pan " << quantity);                        
            movePan(quantity);
            break;
            
        case talky::ArmTopic::eAXIS_TILT_POS:
            LOG4CXX_INFO(logger, "> move tilt " << quantity);                        
            moveTilt(quantity);
            break;

        case talky::ArmTopic::eAXIS_RAD_POS:
            LOG4CXX_INFO(logger, "> move radius " << quantity);                        
            moveRadius(quantity);
            break;

        case talky::ArmTopic::eAXIS_PAN_SPEED:
            LOG4CXX_INFO(logger, "> pan speed " << quantity);                        
            panSpeed(quantity);
            break;
            
        case talky::ArmTopic::eAXIS_TILT_SPEED:
            LOG4CXX_INFO(logger, "> tilt speed " << quantity);                        
            tiltSpeed(quantity);
            break;

        case talky::ArmTopic::eAXIS_RAD_SPEED:
            LOG4CXX_INFO(logger, "> rad speed " << quantity);                        
            radialSpeed(quantity);
            break;
            
        default:
            bret = false;
            LOG4CXX_WARN(logger, "AxisServer: untreated concept " << oCommand.getConcept());           
    }    
    return bret;
}


// AXIS SPEEDS
void AxisServer::panSpeed(float value)
{
    if (pArmInterface != 0)
        pArmInterface->panSpeed(value);
}
void AxisServer::tiltSpeed(float value)
{
    if (pArmInterface != 0)
        pArmInterface->tiltSpeed(value);
}
void AxisServer::radialSpeed(float value)
{
    if (pArmInterface != 0)
        pArmInterface->radialSpeed(value);
}

    // AXIS POSITIONS    
void AxisServer::movePan(float value)
{    
    if (pArmInterface != 0)
        pArmInterface->movePan(value);
}
void AxisServer::moveTilt(float value)
{
    if (pArmInterface != 0)
        pArmInterface->moveTilt(value);
}
void AxisServer::moveRadius(float value)
{
    if (pArmInterface != 0)
        pArmInterface->extend(value);
}
}