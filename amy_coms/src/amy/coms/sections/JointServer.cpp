/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/data/JointCommand.h"
#include "amy/coms/sections/JointServer.h"

namespace amy
{
log4cxx::LoggerPtr JointServer::logger(log4cxx::Logger::getLogger("amy.server"));

JointServer::JointServer()
{    
    pArmInterface = 0;
}

void JointServer::connect2Arm(iArmInterface& oArmInterface)
{
    pArmInterface = &oArmInterface;
}

bool JointServer::processCommand(AmyCommand& oAmyCommand)
{
    bool bret = true;
    float value = oAmyCommand.getValue();

    switch (oAmyCommand.getAction())
    {
        case JointCommand::eJOINT_HS_POS:
            LOG4CXX_INFO(logger, "> set HS " << value);                        
            setPosHS(value);
            break;
            
        case JointCommand::eJOINT_VS_POS:
            LOG4CXX_INFO(logger, "> set VS " << value);                        
            setPosVS(value);
            break;

        case JointCommand::eJOINT_ELB_POS:
            LOG4CXX_INFO(logger, "> set ELB " << value);                        
            setPosELB(value);
            break;

        case JointCommand::eJOINT_HWRI_POS:
            LOG4CXX_INFO(logger, "> set HW " << value);                        
            setPosHW(value);
            break;

        case JointCommand::eJOINT_VWRI_POS:
            LOG4CXX_INFO(logger, "> set VW " << value);                        
            setPosVW(value);
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "JointServer: unknown command " << oAmyCommand.getDescription());           
    }    
    return bret;
}

// JOINT POSITIONS
void JointServer::setPosHS(float value)
{
    if (pArmInterface != 0)
        pArmInterface->moveHS(value);    
}
void JointServer::setPosVS(float value)
{
    if (pArmInterface != 0)
        pArmInterface->moveVS(value);    
}
void JointServer::setPosELB(float value)
{
    if (pArmInterface != 0)
        pArmInterface->moveEL(value);    
}
void JointServer::setPosHW(float value)
{
    if (pArmInterface != 0)
        pArmInterface->moveHW(value);    
}
void JointServer::setPosVW(float value)
{
    if (pArmInterface != 0)
        pArmInterface->moveVW(value);    
}
}