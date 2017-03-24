/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/sections/AxisClient.h"
#include "amy/coms/dictionary/AxisCategory.h"

namespace amy
{

AxisClient::AxisClient()
{
    text = "";
}

// AXIS SPEEDS
void AxisClient::panSpeed(float value)
{
    AxisCommand oAxisCommand(AxisCategory::eAXIS_PAN_SPEED, value);
    updateText(oAxisCommand);
}

void AxisClient::tiltSpeed(float value)
{
    AxisCommand oAxisCommand(AxisCategory::eAXIS_TILT_SPEED, value);
    updateText(oAxisCommand);
}

void AxisClient::radialSpeed(float value)
{
    AxisCommand oAxisCommand(AxisCategory::eAXIS_RAD_SPEED, value);
    updateText(oAxisCommand);
}

// AXIS POSITIONS    
 void AxisClient::movePan(float value)
{
    AxisCommand oAxisCommand(AxisCategory::eAXIS_PAN_POS, value);
    updateText(oAxisCommand);
}
void AxisClient::moveTilt(float value)
{
    AxisCommand oAxisCommand(AxisCategory::eAXIS_TILT_POS, value);
    updateText(oAxisCommand);
}
void AxisClient::moveRadius(float value)
{
    AxisCommand oAxisCommand(AxisCategory::eAXIS_RAD_POS, value);
    updateText(oAxisCommand);
}

void AxisClient::updateText(AxisCommand& oAxisCommand)
{       
    // if valid command, build textual form
    if (oAxisCommand.isValidCommand())
    {
        text = oAxisCommand.buildTextualForm();
    }        
    // otherwise clean text
    else
        text = "";
}

}