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

void AmyComsServer::connect2Arm(iArmInterface& oArmInterface)
{
    pArmInterface = &oArmInterface;
    // connect all section servers to arm interface
    oJointServer.connect2Arm(oArmInterface);
    oAxisServer.connect2Arm(oArmInterface);
    oCyclicServer.connect2Arm(oArmInterface);
    oOtherServer.connect2Arm(oArmInterface);    
    bconnected = true;
}

bool AmyComsServer::isAmyEndRequested()
{
    return oOtherServer.getAmyEndRequested();
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

        switch (oCommand.getCategory())
        {
            case talky::ArmTopic::eCAT_ARM_JOINT:
                bret = oJointServer.processCommand(oCommand);
                break;

            case talky::ArmTopic::eCAT_ARM_AXIS:
                bret = oAxisServer.processCommand(oCommand);
                break;

            case talky::ArmTopic::eCAT_ARM_CYCLIC:
                bret = oCyclicServer.processCommand(oCommand);
                break;

            case talky::ArmTopic::eCAT_ARM_EXTRA:
                bret = oOtherServer.processCommand(oCommand);
                break;

            default:
                LOG4CXX_WARN(logger, "AmyComsServer: no processing for this category " << oCommand.getCategory());                        
        }                
    }
    else
    {
        LOG4CXX_WARN(logger, "AmyComsServer: msg processing failed!");            
        LOG4CXX_WARN(logger, "AmyComsServer: " + oInterpreter.getMessage().toStringValidity());            
    }
            
    return bret;
}

}