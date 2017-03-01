/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/AmyClient.h"

namespace amy
{

AmyClient::AmyClient()
{    
}
void AmyClient::movePan(float value)
{
    int category = AmyCommand::eCAT_AXIS_CMD;
    int action = AmyCommand::eAXIS_PAN_POS;
    if (oAmyCommand.buildCommand(category, action, value))
        sendCommand();    
}

void AmyClient::moveTilt(float value)
{
    int category = AmyCommand::eCAT_AXIS_CMD;
    int action = AmyCommand::eAXIS_TILT_POS;
    if (oAmyCommand.buildCommand(category, action, value))
        sendCommand();    
}

void AmyClient::moveRadius(float value)
{
    int category = AmyCommand::eCAT_AXIS_CMD;
    int action = AmyCommand::eAXIS_RAD_POS;
    if (oAmyCommand.buildCommand(category, action, value))
        sendCommand();    
}

void AmyClient::setPosHS(float value)
{
    int category = AmyCommand::eCAT_JOINT_CMD;
    int action = AmyCommand::eJOINT_HS_POS;
    if (oAmyCommand.buildCommand(category, action, value))
        sendCommand();        
}

void AmyClient::setPosVS(float value)
{
    int category = AmyCommand::eCAT_JOINT_CMD;
    int action = AmyCommand::eJOINT_VS_POS;
    if (oAmyCommand.buildCommand(category, action, value))
        sendCommand();            
}

void AmyClient::setPosELB(float value)
{
    int category = AmyCommand::eCAT_JOINT_CMD;
    int action = AmyCommand::eJOINT_ELB_POS;
    if (oAmyCommand.buildCommand(category, action, value))
        sendCommand();            
}

void AmyClient::setPosHW(float value)
{
    int category = AmyCommand::eCAT_JOINT_CMD;
    int action = AmyCommand::eJOINT_HWRI_POS;
    if (oAmyCommand.buildCommand(category, action, value))
        sendCommand();        
}

void AmyClient::setPosVW(float value)
{
    int category = AmyCommand::eCAT_JOINT_CMD;
    int action = AmyCommand::eJOINT_VWRI_POS;
    if (oAmyCommand.buildCommand(category, action, value))
        sendCommand();            
}

void AmyClient::endAmy()
{
    int category = AmyCommand::eCAT_AMY_CMD;
    int action = AmyCommand::eAMY_END;
    if (oAmyCommand.buildCommand(category, action))
        sendCommand();        
}

void AmyClient::toDoCommand()
{
    // nothing done
    // dummy method for to do commands
}
}