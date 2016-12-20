/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/client/AmyClient.h"

namespace amy
{

AmyClient::AmyClient()
{    
}

void AmyClient::movePan(float value)
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_MOVE_ARM, AmyCommand::eTAR_PAN, value))
        sendCommand();    
}

void AmyClient::moveTilt(float value)
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_MOVE_ARM, AmyCommand::eTAR_TILT, value))
        sendCommand();    
}

void AmyClient::moveRadius(float value)
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_MOVE_ARM, AmyCommand::eTAR_RADIUS, value))
        sendCommand();    
}

void AmyClient::setPosHS(float value)
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_MOVE_JOINT, AmyCommand::eTAR_JOINT_HSHOULDER, value))
        sendCommand();        
}

void AmyClient::setPosVS(float value)
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_MOVE_JOINT, AmyCommand::eTAR_JOINT_VSHOULDER, value))
        sendCommand();            
}

void AmyClient::setPosELB(float value)
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_MOVE_JOINT, AmyCommand::eTAR_JOINT_ELBOW, value))
        sendCommand();            
}

void AmyClient::setPosHW(float value)
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_MOVE_JOINT, AmyCommand::eTAR_JOINT_HWRIST, value))
        sendCommand();        
}

void AmyClient::setPosVW(float value)
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_MOVE_JOINT, AmyCommand::eTAR_JOINT_VWRIST, value))
        sendCommand();            
}

void AmyClient::endAmy()
{
    if (oAmyCommand.buildCommand(AmyCommand::eACT_END_AMY, AmyCommand::eTAR_PROGRAM))
        sendCommand();        
}


}