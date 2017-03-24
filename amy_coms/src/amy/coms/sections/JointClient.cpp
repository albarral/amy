/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/sections/JointClient.h"
#include "amy/coms/dictionary/JointCategory.h"

namespace amy
{

JointClient::JointClient()
{
    text = "";
}

// JOINT POSITIONS
void JointClient::setPosHS(float value)
{
    JointCommand oJointCommand(JointCategory::eJOINT_HS_POS, value);
    updateText(oJointCommand);
}

void JointClient::setPosVS(float value)
{
    JointCommand oJointCommand(JointCategory::eJOINT_VS_POS, value);
    updateText(oJointCommand);
}

void JointClient::setPosELB(float value)
{
    JointCommand oJointCommand(JointCategory::eJOINT_ELB_POS, value);
    updateText(oJointCommand);    
}

void JointClient::setPosHW(float value)
{
    JointCommand oJointCommand(JointCategory::eJOINT_HWRI_POS, value);
    updateText(oJointCommand);
}

void JointClient::setPosVW(float value)
{
    JointCommand oJointCommand(JointCategory::eJOINT_VWRI_POS, value);
    updateText(oJointCommand);
}

void JointClient::updateText(JointCommand& oJointCommand)
{       
    // if valid command, build textual form
    if (oJointCommand.isValidCommand())
    {
        text = oJointCommand.buildTextualForm();
    }        
    // otherwise clean text
    else
        text = "";
}

}