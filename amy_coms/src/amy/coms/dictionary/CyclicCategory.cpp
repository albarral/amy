/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/dictionary/CyclicCategory.h"
#include "amy/coms/dictionary/ComsCommand.h"

namespace amy
{
CyclicCategory::CyclicCategory() : ComsCategory(ComsCategory::eCATEGORY_CYCLIC, "cyclic category")   
{
    // builds list of commands
    build();
}

void CyclicCategory::build()
{
    listCommands.clear();
    
    // define pan cyclic commands
    ComsCommand oCommand(ID, CyclicCategory::eCYCLIC_PAN_FREQ, "panfreq", 1, "set frequency of pan cycles (Hz)");    
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_PAN_AMP, "panamp", 1, "set amplitude of pan cycles (degrees)");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_PAN_TRIGGER, "pantrig", 0, "trigger pan cyclic movement");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_PAN_STOP, "panstop", 0, "stop pan cyclic movement");
    listCommands.push_back(oCommand);
}
}