/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream>
#include "amy/coms/AmyFileClient.h"

namespace amy
{

AmyFileClient::AmyFileClient()
{    
    filename = "test.txt";
    oFile.open(filename);   // no append mode
}


void AmyFileClient::movePan(float value)
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_MOVE_ARM, AmyCommand::eTAR_PAN, value))
        sendCommand();    
}

void AmyFileClient::moveTilt(float value)
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_MOVE_ARM, AmyCommand::eTAR_TILT, value))
        sendCommand();    
}

void AmyFileClient::moveRadius(float value)
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_MOVE_ARM, AmyCommand::eTAR_RADIUS, value))
        sendCommand();    
}

void AmyFileClient::endAmy()
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_END_AMY, AmyCommand::eTAR_PROGRAM))
        sendCommand();        
}

void AmyFileClient::sendCommand()
{
    std::cout << "command: " << oAmyCommand.getText() << std::endl;
    if (oFile.open(filename))        
    {
        oFile.goTop();
        oFile.writeFlush(oAmyCommand.getText());
    }
}


}