/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/sections/OtherClient.h"

namespace amy
{

OtherClient::OtherClient()
{
    text = "";
}

void OtherClient::keepTilt(int value)
{
    OtherCommand oOtherCommand(OtherCommand::eOTHER_KEEP_TILT, value);
    updateText(oOtherCommand);
}

void OtherClient::endAmy()
{
    OtherCommand oOtherCommand(OtherCommand::eOTHER_AMY_END);
    updateText(oOtherCommand);
}

void OtherClient::updateText(OtherCommand& oOtherCommand)
{       
    // if valid command, build textual form
    if (oOtherCommand.isValidCommand())
    {
        text = oOtherCommand.buildTextualForm();
    }        
    // otherwise clean text
    else
        text = "";
}

}