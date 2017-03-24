/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/coms/AmyServer.h"
#include "amy/coms/data/AmyCommand.h"
#include "amy/coms/dictionary/ComsCategory.h"

namespace amy
{
log4cxx::LoggerPtr AmyServer::logger(log4cxx::Logger::getLogger("amy.server"));

AmyServer::AmyServer()
{    
    bconnected = false;
    pArmInterface = 0;
}

void AmyServer::connect2Arm(iArmInterface& oArmInterface)
{
    pArmInterface = &oArmInterface;
    // connect all section servers to arm interface
    oJointServer.connect2Arm(oArmInterface);
    oAxisServer.connect2Arm(oArmInterface);
    oCyclicServer.connect2Arm(oArmInterface);
    oOtherServer.connect2Arm(oArmInterface);    
    bconnected = true;
}

bool AmyServer::isAmyEndRequested()
{
    return oOtherServer.getAmyEndRequested();
}
    
bool AmyServer::processCommand(std::string text)
{
    bool bret = false;

    // interpret command
    if (oComsInterpreter.checkCommand(text))
    {            
        // if command interpreted, check its validity
        AmyCommand oAmyCommand = oComsInterpreter.getCommand();
        
        // if valid command, process call to arm
        if (oAmyCommand.isValidCommand())
        {
            switch (oAmyCommand.getCategory())
            {
                case ComsCategory::eCATEGORY_JOINTS:
                    bret = oJointServer.processCommand(oAmyCommand);
                    break;

                case ComsCategory::eCATEGORY_AXIS:
                    bret = oAxisServer.processCommand(oAmyCommand);
                    break;

                case ComsCategory::eCATEGORY_CYCLIC:
                    bret = oCyclicServer.processCommand(oAmyCommand);
                    break;

                case ComsCategory::eCATEGORY_OTHER:
                    bret = oOtherServer.processCommand(oAmyCommand);
                    break;

                default:
                    LOG4CXX_WARN(logger, "AmyServer: no processing for this category " << oAmyCommand.getCategory());                        
            }                
        }
        // unknown command
        else
            LOG4CXX_WARN(logger, "AmyServer: unknown command " << text);                                    
    }
    // invalid command (could not be interpreted)
    else
        LOG4CXX_WARN(logger, "AmyServer: malformed command " << text);                        
        
    return bret;
}

}