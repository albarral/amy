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


// ARM MOVER
void CyclicClient::launchMove(int value)
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_MOVER_LAUNCH, value);
    updateText(oCyclicCommand);
}

void CyclicClient::stopMove()
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_MOVER_STOP);
    updateText(oCyclicCommand);
}

void CyclicClient::turnMove(int value)
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_MOVER_TURN, value);
    updateText(oCyclicCommand);
}

void CyclicClient::moveWider(bool value)
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_MOVER_WIDER, (value ? 1 : 0));
    updateText(oCyclicCommand);
}

void CyclicClient::moveTaller(bool value)
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_MOVER_TALLER, (value ? 1 : 0));
    updateText(oCyclicCommand);
}
void CyclicClient::moveFaster(bool value)
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_MOVER_FASTER, (value ? 1 : 0));
    updateText(oCyclicCommand);
}

// FRONTAL CYCLER
// set front cyclic frequency
void CyclicClient::frontFrequency(float value)
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_FRONT_FREQ, value);
    updateText(oCyclicCommand);
}

// set front amplitude (degrees)
void CyclicClient::frontAmplitude(float value)
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_FRONT_AMP, value);
    updateText(oCyclicCommand);
}

// set front cyclic angle
void CyclicClient::frontAngle(float value)
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_FRONT_ANGLE, value);
    updateText(oCyclicCommand);
}

// start front cyclic movement
void CyclicClient::frontStart()
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_FRONT_START);
    updateText(oCyclicCommand);
}

// stop front cyclic movement
void CyclicClient::frontStop()
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_FRONT_STOP);
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