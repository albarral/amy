/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/AmyComs.h"

namespace amy
{

AmyComs::AmyComs()
{    
    oFile.setAppendMode(true);
    filename = "test.txt";
}


void AmyComs::movePan(float value)
{
    int action = AmyCommand::eACT_MOVE_ARM;
    int target = AmyCommand::eTAR_PAN;
    
    if (oAmyCommand.buildCommand(action, target, value))
        sendCommand(oAmyCommand.getText());    
}

void AmyComs::sendCommand(std::string text)
{
    if (oFile.open(filename))        
    {
        oFile.writeFlush(text);
    }
}


}