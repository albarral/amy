/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/sections/OtherServer.h"
#include "talky/topics/ArmTopic.h"


namespace amy
{
log4cxx::LoggerPtr OtherServer::logger(log4cxx::Logger::getLogger("amy.coms"));

OtherServer::OtherServer()
{    
    pArmInterface = 0;
    bamyEndRequested = false;
}

void OtherServer::connect2Arm(iArmInterface& oArmInterface)
{
    pArmInterface = &oArmInterface;
}

bool OtherServer::processCommand(talky::Command& oCommand)
{
    bool bret = true;
    float quantity = oCommand.getQuantity();
    
    switch (oCommand.getConcept())
    {
        case talky::ArmTopic::eEXTRA_ARM_STOP:
            LOG4CXX_INFO(logger, "> arm stop ");                        
            toDoCommand(quantity);
            break;
            
        case talky::ArmTopic::eEXTRA_KEEP_TILT:
            LOG4CXX_INFO(logger, "> keep tilt " << quantity);                        
            keepTilt((int)quantity);
            break;
            
        case talky::ArmTopic::eEXTRA_AMY_END:
            LOG4CXX_INFO(logger, "> end emy");                        
            endAmy();
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "OtherServer: untreated action " << oCommand.getConcept());           
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