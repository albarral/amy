/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/sections/JointServer.h"
#include "talky/topics/ArmTopic.h"

namespace amy
{
log4cxx::LoggerPtr JointServer::logger(log4cxx::Logger::getLogger("amy.coms"));

JointServer::JointServer()
{    
    pArmInterface = 0;
}

void JointServer::connect2Arm(iArmInterface& oArmInterface)
{
    pArmInterface = &oArmInterface;
}

bool JointServer::processCommand(talky::Command& oCommand)
{
    bool bret = true;
    float quantity = oCommand.getQuantity();

    switch (oCommand.getConcept())
    {
        case talky::ArmTopic::eJOINT_HS_POS:
            LOG4CXX_INFO(logger, "> set HS " << quantity);                        
            setPosHS(quantity);
            break;
            
        case talky::ArmTopic::eJOINT_VS_POS:
            LOG4CXX_INFO(logger, "> set VS " << quantity);                        
            setPosVS(quantity);
            break;

        case talky::ArmTopic::eJOINT_ELB_POS:
            LOG4CXX_INFO(logger, "> set ELB " << quantity);                        
            setPosELB(quantity);
            break;

        case talky::ArmTopic::eJOINT_HWRI_POS:
            LOG4CXX_INFO(logger, "> set HW " << quantity);                        
            setPosHW(quantity);
            break;

        case talky::ArmTopic::eJOINT_VWRI_POS:
            LOG4CXX_INFO(logger, "> set VW " << quantity);                        
            setPosVW(quantity);
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "JointServer: untreated concept " << oCommand.getConcept());           
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