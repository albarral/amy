/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/dictionary/OtherCategory.h"
#include "amy/coms/dictionary/ComsCommand.h"

namespace amy
{
OtherCategory::OtherCategory() : ComsCategory(ComsCategory::eCATEGORY_OTHER, "other category")   
{
    // builds list of commands
    build();
}

void OtherCategory::build()
{
    listCommands.clear();
    
    // define pan cyclic commands
    ComsCommand oCommand(ID, OtherCategory::eOTHER_ARM_STOP, "stop", 0, "stop arm");    
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, OtherCategory::eOTHER_KEEP_TILT, "keep", 0, "keep the tilt position");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, OtherCategory::eOTHER_AMY_END, "end", 0, "end amy process");
    listCommands.push_back(oCommand);
}

bool OtherCategory::isValidAction(int value)
{
    return (value > OtherCategory::eOTHER_UNDEF && value < OtherCategory::eOTHER_DIM);
}

}