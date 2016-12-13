/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cstdlib>  // for getenv
#include <iostream>

#include "amy/server/AmyFileServer.h"

namespace amy
{

AmyFileServer::AmyFileServer()
{    
    char* pVar = getenv("HOME");
    
    if (pVar!=NULL)
    {
        std::string home(pVar);
        filename = home + "/coms/amy_in.txt";
        oFile.open(filename);   // no append mode
    }
}


void AmyFileServer::movePan(float value)
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_MOVE_ARM, AmyCommand::eTAR_PAN, value))
        sendCommand();    
}

void AmyFileServer::moveTilt(float value)
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_MOVE_ARM, AmyCommand::eTAR_TILT, value))
        sendCommand();    
}

void AmyFileServer::moveRadius(float value)
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_MOVE_ARM, AmyCommand::eTAR_RADIUS, value))
        sendCommand();    
}

void AmyFileServer::endAmy()
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_END_AMY, AmyCommand::eTAR_PROGRAM))
        sendCommand();        
}

void AmyFileServer::sendCommand()
{
    std::cout << "command: " << oAmyCommand.getText() << std::endl;
    if (oFile.open(filename))        
    {
        oFile.goTop();
        oFile.writeFlush(oAmyCommand.getText());
    }
}


}