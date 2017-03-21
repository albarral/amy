/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/sections/CyclicClient.h"

namespace amy
{

CyclicClient::CyclicClient()
{
    text = "";
}

// CYCLIC MOVEMENTS
void CyclicClient::panFrequency(float value)
{
    CyclicCommand oCyclicCommand(CyclicCommand::eCYCLIC_PAN_FREQ, value);
    updateText(oCyclicCommand);
}

// set pan amplitude (degrees)
void CyclicClient::panAmplitude(float value)
{
    CyclicCommand oCyclicCommand(CyclicCommand::eCYCLIC_PAN_AMP, value);
    updateText(oCyclicCommand);
}

// trigger pan cyclic movement
void CyclicClient::panTrigger()
{
    CyclicCommand oCyclicCommand(CyclicCommand::eCYCLIC_PAN_TRIGGER);
    updateText(oCyclicCommand);
}

// stop pan cyclic movement
void CyclicClient::panStop()
{
    CyclicCommand oCyclicCommand(CyclicCommand::eCYCLIC_PAN_STOP);
    updateText(oCyclicCommand);
}


void CyclicClient::updateText(CyclicCommand& oCyclicCommand)
{       
    // if valid command, build textual form
    if (oCyclicCommand.isValidCommand())
    {
        text = oCyclicCommand.buildTextualForm();
    }        
    // otherwise clean text
    else
        text = "";
}

}