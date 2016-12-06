/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/AmyComsFile.h"

namespace amy
{

AmyComsFile::AmyComsFile()
{    
    filename = "test.txt";
    oFile.open(filename);   // no append mode
}


void AmyComsFile::movePan(float value)
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_MOVE_ARM, AmyCommand::eTAR_PAN, value))
        sendCommand();    
}

void AmyComsFile::moveTilt(float value)
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_MOVE_ARM, AmyCommand::eTAR_TILT, value))
        sendCommand();    
}

void AmyComsFile::moveRadius(float value)
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_MOVE_ARM, AmyCommand::eTAR_RADIUS, value))
        sendCommand();    
}

void AmyComsFile::endAmy()
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_END_AMY, AmyCommand::eTAR_PROGRAM))
        sendCommand();        
}

void AmyComsFile::sendCommand()
{
    if (oFile.open(filename))        
    {
        oFile.goTop();
        oFile.writeFlush(oAmyCommand.getText());
    }
}


}