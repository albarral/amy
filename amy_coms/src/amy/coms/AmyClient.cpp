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

void AmyClient::sendJointCommand()
{
    sendCommand(oJointClient.getCommand());    
}

void AmyClient::sendAxisCommand()
{
    sendCommand(oAxisClient.getCommand());        
}

void AmyClient::sendCyclicCommand()
{
    sendCommand(oCyclicClient.getCommand());        
}

void AmyClient::sendOtherCommand()
{
    sendCommand(oOtherClient.getCommand());        
}

void AmyClient::toDoCommand()
{
    // nothing done
    // dummy method for to do commands
}

}