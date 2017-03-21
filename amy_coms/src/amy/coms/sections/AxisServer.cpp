/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/data/AxisCommand.h"
#include "amy/coms/sections/AxisServer.h"

namespace amy
{
log4cxx::LoggerPtr AxisServer::logger(log4cxx::Logger::getLogger("amy.server"));

AxisServer::AxisServer()
{    
    pArmInterface = 0;
}

void AxisServer::connect2Arm(iArmInterface& oArmInterface)
{
    pArmInterface = &oArmInterface;
}

bool AxisServer::processCommand(AmyCommand& oAmyCommand)
{
    bool bret = true;
    float value = oAmyCommand.getValue();
    
    switch (oAmyCommand.getAction())
    {
        case AxisCommand::eAXIS_PAN_POS:
            LOG4CXX_INFO(logger, "> move pan " << value);                        
            movePan(value);
            break;
            
        case AxisCommand::eAXIS_TILT_POS:
            LOG4CXX_INFO(logger, "> move tilt " << value);                        
            moveTilt(value);
            break;

        case AxisCommand::eAXIS_RAD_POS:
            LOG4CXX_INFO(logger, "> move radius " << value);                        
            moveRadius(value);
            break;

        case AxisCommand::eAXIS_PAN_SPEED:
            LOG4CXX_INFO(logger, "> pan speed " << value);                        
            panSpeed(value);
            break;
            
        case AxisCommand::eAXIS_TILT_SPEED:
            LOG4CXX_INFO(logger, "> tilt speed " << value);                        
            tiltSpeed(value);
            break;

        case AxisCommand::eAXIS_RAD_SPEED:
            LOG4CXX_INFO(logger, "> rad speed " << value);                        
            radialSpeed(value);
            break;
            
        default:
            bret = false;
            LOG4CXX_WARN(logger, "AxisServer: unknown command " << oAmyCommand.getDescription());           
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