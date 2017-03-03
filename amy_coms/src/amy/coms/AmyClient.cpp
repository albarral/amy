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

    // AXIS SPEEDS
void AmyClient::panSpeed(float value)
{
    int category = AmyCommand::eCAT_AXIS_CMD;
    int action = AmyCommand::eAXIS_PAN_SPEED;
    if (oAmyCommand.buildCommand(category, action, value))
        sendCommand();        
}
void AmyClient::tiltSpeed(float value)
{
    int category = AmyCommand::eCAT_AXIS_CMD;
    int action = AmyCommand::eAXIS_TILT_SPEED;
    if (oAmyCommand.buildCommand(category, action, value))
        sendCommand();            
}
void AmyClient::radialSpeed(float value)
{
    int category = AmyCommand::eCAT_AXIS_CMD;
    int action = AmyCommand::eAXIS_RAD_SPEED;
    if (oAmyCommand.buildCommand(category, action, value))
        sendCommand();            
}
void AmyClient::keepTilt(int value)
{
    int category = AmyCommand::eCAT_ARM_CMD;
    int action = AmyCommand::eARM_KEEP_TILT;
    if (oAmyCommand.buildCommand(category, action, value))
        sendCommand();            
}

    // AXIS POSITIONS    
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

    // JOINT POSITIONS
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

// AMY COMMANDS
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