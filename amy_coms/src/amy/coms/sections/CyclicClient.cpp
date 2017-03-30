/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/sections/CyclicClient.h"
#include "amy/coms/dictionary/CyclicCategory.h"

namespace amy
{

CyclicClient::CyclicClient()
{
    text = "";
}

// set pan cyclic frequency
void CyclicClient::panFrequency(float value)
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_PAN_FREQ, value);
    updateText(oCyclicCommand);
}

// set pan amplitude (degrees)
void CyclicClient::panAmplitude(float value)
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_PAN_AMP, value);
    updateText(oCyclicCommand);
}

// trigger pan cyclic movement
void CyclicClient::panTrigger()
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_PAN_TRIGGER);
    updateText(oCyclicCommand);
}

// stop pan cyclic movement
void CyclicClient::panStop()
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_PAN_STOP);
    updateText(oCyclicCommand);
}

void CyclicClient::tiltFrequency(float value)
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_TILT_FREQ, value);
    updateText(oCyclicCommand);
}

// set tilt amplitude (degrees)
void CyclicClient::tiltAmplitude(float value)
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_TILT_AMP, value);
    updateText(oCyclicCommand);
}

// trigger tilt cyclic movement
void CyclicClient::tiltTrigger()
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_TILT_TRIGGER);
    updateText(oCyclicCommand);
}

// stop tilt cyclic movement
void CyclicClient::tiltStop()
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_TILT_STOP);
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