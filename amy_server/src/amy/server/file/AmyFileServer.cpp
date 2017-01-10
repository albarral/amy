/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <iostream>

#include "amy/server/file/AmyFileServer.h"
#include "amy/coms/AmyComsConfig.h"

namespace amy
{
log4cxx::LoggerPtr AmyFileServer::logger(log4cxx::Logger::getLogger("amy.server"));

AmyFileServer::AmyFileServer()
{    
    // get coms file name
    AmyComsConfig oAmyComsConfig;    
    filename = oAmyComsConfig.getComsFilename();
    // open coms file for reading & writing
    if (!filename.empty())
    {
        oFileReader.open(filename);   
        oFileWriter.open(filename);   
    }
}

AmyFileServer::~AmyFileServer()
{
    oFileReader.close();
    oFileWriter.close();    
}

bool AmyFileServer::readCommand()
{
    bool brequest = false;  // default no request received

    if (oFileReader.isOpen())        
    {
        // read file from top
        oFileReader.readFromTop();
        //LOG4CXX_INFO(logger, "AmyFileServer: read pos " << oFileReader.getPos());
        std::string text = oFileReader.readLine();
        
        // and clear it
        oFileWriter.writeFromTop();
        oFileWriter.writeFlush("\n");

        // if request received, interpret it
        if (!text.empty())
        {
            brequest = true;
            bvalid = oAmyCommand.interpret(text);
            LOG4CXX_DEBUG(logger, "AmyFileServer: command = " << oAmyCommand.getDescription());
        }        
    }
    else
    {
        LOG4CXX_ERROR(logger, "AmyFileServer: could not open coms file " << filename);
    }
    
    return brequest;
}

void AmyFileServer::processCommand()
{
    switch (oAmyCommand.getAction())
    {
        case AmyCommand::eACT_MOVE_ARM:
            processArmCommand();
            break;
            
        case AmyCommand::eACT_MOVE_JOINT:
            processJointCommand();
            break;

        case AmyCommand::eACT_END_AMY:
            LOG4CXX_INFO(logger, "> end amy");                        
            endAmy();
            break;

        default:
            LOG4CXX_WARN(logger, "AmyFileServer: unknown action");                        
    }    
}

void AmyFileServer::processArmCommand()
{
    float value = oAmyCommand.getValue();

    switch (oAmyCommand.getTarget())
    {
        case AmyCommand::eTAR_PAN:
            LOG4CXX_INFO(logger, "> move pan " << value);                        
            AmyServer::movePan(value);
            break;
            
        case AmyCommand::eTAR_TILT:
            LOG4CXX_INFO(logger, "> move tilt " << value);                        
            AmyServer::moveTilt(value);
            break;

        case AmyCommand::eTAR_RADIUS:
            LOG4CXX_INFO(logger, "> move radius " << value);                        
            AmyServer::moveRadius(value);
            break;

        default:
            LOG4CXX_WARN(logger, "AmyFileServer: unknown arm target");                        
    }    
}

void AmyFileServer::processJointCommand()
{
    float value = oAmyCommand.getValue();

    switch (oAmyCommand.getTarget())
    {
        case AmyCommand::eTAR_JOINT_HSHOULDER:
            LOG4CXX_INFO(logger, "> set HS " << value);                        
            AmyServer::setPosHS(value);
            break;
            
        case AmyCommand::eTAR_JOINT_VSHOULDER:
            LOG4CXX_INFO(logger, "> set VS " << value);                        
            AmyServer::setPosVS(value);
            break;

        case AmyCommand::eTAR_JOINT_ELBOW:
            LOG4CXX_INFO(logger, "> set ELB " << value);                        
            AmyServer::setPosELB(value);
            break;

        case AmyCommand::eTAR_JOINT_HWRIST:
            LOG4CXX_INFO(logger, "> set HW " << value);                        
            AmyServer::setPosHW(value);
            break;

        case AmyCommand::eTAR_JOINT_VWRIST:
            LOG4CXX_INFO(logger, "> set VW " << value);                        
            AmyServer::setPosVW(value);
            break;

        default:
            LOG4CXX_WARN(logger, "AmyFileServer: unknown joint target");                        
    }    
}

}