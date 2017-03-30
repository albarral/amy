/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/dictionary/ComsCommand.h"

namespace amy
{
ComsCommand::ComsCommand()
{
    category = 0;    
    ID = 0;
    name = "";
    numElements = 0;
    description = "";
}

ComsCommand::ComsCommand(int category, int ID, std::string name, int numElements, std::string description)
{
    this->category = category;
    this->ID = ID;
    this->name = name;
    this->numElements = numElements;
    this->description = description;    
}

std::string ComsCommand::toString()
{
    std::string desc = "ComsCommand: [id="  + std::to_string(ID) +
            ", category=" + std::to_string(category) +
            ", name=" + name + 
            ", numElements=" + std::to_string(numElements) + 
            ", desc=" + description + "]\n";
    
    return desc;    
}

}