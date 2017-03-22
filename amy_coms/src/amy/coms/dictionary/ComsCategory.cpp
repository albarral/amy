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
    return (cat > eCATEGORY_UNDEF && cat < eCATEGORY_DIM);    
}

//void ComsCategory::build()
//{
//    // nothing done
//    listCommands.clear();
//}

std::string ComsCategory::toString()
{
    std::string desc = "ComsCategory: [id="  + std::to_string(ID) + ", name=" + name + "]\n";
    
    for (ComsCommand oCommand: listCommands)
    {
        desc += oCommand.toString() + "\n";
    }

    return desc;    
}

}