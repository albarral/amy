/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/dictionary/ComsCategory.h"

namespace amy
{
ComsCategory::ComsCategory()
{
    ID = eCATEGORY_UNDEF;   
    name = "undef";
}

ComsCategory::ComsCategory(int ID, std::string name)
{
    this->ID = ID;
    this->name = name;
}

ComsCategory::~ComsCategory()
{
    listCommands.clear();    
}

bool ComsCategory::isValidCategory(int cat)
{
    return (cat > ComsCategory::eCATEGORY_UNDEF && cat < ComsCategory::eCATEGORY_DIM);    
}

std::string ComsCategory::toString()
{
    std::string desc = "ComsCategory: [id="  + std::to_string(ID) + ", name=" + name + "]\n";
    
    for (ComsCommand oCommand: listCommands)
    {
        desc += oCommand.toString() + "\n";
    }

    return desc;    
}

std::string ComsCategory::describeCategory(int value)
{
    std::string desc;
    switch (value)
    {
        case ComsCategory::eCATEGORY_UNDEF:
            desc = "undefined";
            break;
        case ComsCategory::eCATEGORY_JOINTS:
            desc = "joint";
            break;
        case ComsCategory::eCATEGORY_AXIS:
            desc = "axis";
            break;
        case ComsCategory::eCATEGORY_CYCLIC:
            desc = "cyclic";
            break;
        case ComsCategory::eCATEGORY_OTHER:
            desc = "other";
            break;
            
        default:
            desc = "invalid";           
    }
    return desc;    
}

}