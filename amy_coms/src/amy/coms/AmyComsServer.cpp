/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
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
        // simple message received
        if (!oInterpreter.isBlockProcessed())
        {
            // get interpreted command
            talky::Command& oCommand = oInterpreter.getCommand();
            // and process it, transforming it to a proper arm interface call
            bret = oArmComsControl.processCommand(oCommand);
            
            if (bret)
            {
                LOG4CXX_INFO(logger, "AmyComsServer: command ok - " + oCommand.toString());                    
            }                
            else
                LOG4CXX_WARN(logger, "AmyComsServer: command failed - " + oCommand.toString());                                    
        }
        // message block received
        else
        {            
            // process interpreted commands
            bret = processCommandBlock(oInterpreter.getCommandBlock());
        }
    }
    else
    {
        LOG4CXX_WARN(logger, "AmyComsServer: msg processing failed!");            
    }
            
    return bret;
}

bool AmyComsServer::processCommandBlock(talky::CommandBlock& oCommandBlock)
{
    int numWellProcessed = 0;

    // for each interpreted command
    for (talky::Command& oCommand : oCommandBlock.getListCommands())
    {
        // process it, transforming it to a proper arm interface call        
        if (oArmComsControl.processCommand(oCommand))
        {
            numWellProcessed++;
            LOG4CXX_INFO(logger, "AmyComsServer: command ok - " + oCommand.toString());                    
        }                
        else
            LOG4CXX_WARN(logger, "AmyComsServer: command failed - " + oCommand.toString());                                            
    }

    // return true if all commands well processed
    return (numWellProcessed == oCommandBlock.getListCommands().size());
}

}