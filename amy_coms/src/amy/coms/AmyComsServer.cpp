/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/coms/AmyComsServer.h"
#include "talky/Topics.h"
#include "talky/coms/Command.h"
#include "talky/topics/ArmTopic.h"


namespace amy
{
log4cxx::LoggerPtr AmyComsServer::logger(log4cxx::Logger::getLogger("amy.coms"));

AmyComsServer::AmyComsServer()
{    
    bconnected = false;
    pArmInterface = 0;
    // prepare interpreter for arm topic communications
    oInterpreter.addLanguage(talky::Topics::eTOPIC_ARM);
}

void AmyComsServer::connect2Arm(iArmInterface* pArmInterface)
{
    this->pArmInterface = pArmInterface;
    if (pArmInterface != 0)
    {
        // connect controller to arm interface
        oArmComsControl.connect2Arm(pArmInterface);
        bconnected = true;
    }
    else
        bconnected = false;
}

bool AmyComsServer::isAmyEndRequested()
{
    return oArmComsControl.getAmyEndRequested();
}
    
bool AmyComsServer::processMessage(std::string text)
{
    bool bret = false;

    // interpret message
    if (oInterpreter.processMessage(text))
    {
        // show obtained command
        talky::Command& oCommand = oInterpreter.getCommand();
        LOG4CXX_INFO(logger, "AmyComsServer: msg processed ok");        
        LOG4CXX_INFO(logger, "AmyComsServer: " + oCommand.toString());    

        // and process command (convert to arm interface control)
        oArmComsControl.processCommand(oCommand);
    }
    else
    {
        LOG4CXX_WARN(logger, "AmyComsServer: msg processing failed!");            
        LOG4CXX_WARN(logger, "AmyComsServer: " + oInterpreter.getMessage().toStringValidity());            
    }
            
    return bret;
}

}