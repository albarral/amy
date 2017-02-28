/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/console/UserCommand.h"

namespace amy
{

// Constructor 
UserCommand::UserCommand()
{
    name = "";
    code = 0;
    type = 0;
    desc = "";    
}

// Constructor 
UserCommand::UserCommand(std::string name, int code, int type, std::string desc)
{    
    this->name = name;
    this->code = code;
    this->type = type;
    this->desc = desc;
 }
}