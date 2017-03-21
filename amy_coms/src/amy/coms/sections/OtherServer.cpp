/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/data/JointCommand.h"
#include "amy/coms/sections/OtherServer.h"
#include "amy/coms/data/OtherCommand.h"

namespace amy
{
log4cxx::LoggerPtr OtherServer::logger(log4cxx::Logger::getLogger("amy.server"));

OtherServer::OtherServer()
{    
    pArmInterface = 0;
    bamyEndRequested = false;
}

void OtherServer::connect2Arm(iArmInterface& oArmInterface)
{
    pArmInterface = &oArmInterface;
}

bool OtherServer::processCommand(AmyCommand& oAmyCommand)
{
    bool bret = true;
    float value = oAmyCommand.getValue();
    
    switch (oAmyCommand.getAction())
    {
        case OtherCommand::eOTHER_ARM_STOP:
            LOG4CXX_INFO(logger, "> arm stop ");                        
            toDoCommand(value);
            break;
            
        case OtherCommand::eOTHER_KEEP_TILT:
            LOG4CXX_INFO(logger, "> keep tilt " << value);                        
            keepTilt((int)value);
            break;
            
        case OtherCommand::eOTHER_AMY_END:
            LOG4CXX_INFO(logger, "> end emy");                        
            endAmy();
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "OtherServer: unknown command " << oAmyCommand.getDescription());           
    }    
    return bret;
}

void OtherServer::keepTilt(int value)
{
    if (pArmInterface != 0)
        pArmInterface->keepTilt(value);
}

void OtherServer::endAmy()
{
    bamyEndRequested = true;    
}

void OtherServer::toDoCommand(float value)
{
    // nothing done
    // dummy method for to do commands
    LOG4CXX_INFO(logger, "> to do");                        
}

}