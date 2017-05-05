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
    
    int needsValue = 1; // command needs an extra value
    int noValue = 0;      // command doesn't need an extra value
    
    // commands definition for all cyclic movements 
    // FRONTAL CYCLER
    ComsCommand oCommand(ID, CyclicCategory::eCYCLIC_FRONT_FREQ, "f1", needsValue, "set frequency of frontal cycler (Hz)");    
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_FRONT_AMP, "amp1", needsValue, "set amplitude of frontal cycler (degrees)");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_FRONT_ANGLE, "ang1", needsValue, "set orientation of frontal cycler (degrees)");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_FRONT_START, "go1", noValue, "start frontal cycler movement");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_FRONT_STOP, "end1", noValue, "stop frontal cycler movement");
    listCommands.push_back(oCommand);
    // ARM MOVER
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_MOVER_LAUNCH, "mov", needsValue, "launch specified movement (type)");    
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_MOVER_STOP, "m0", noValue, "stops cyclic movement");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_MOVER_TURN, "tur", needsValue, "turns cyclic movement (degrees)");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_MOVER_WIDER, "wid", needsValue, "makes cyclic movement wider (1) or narrower (0)");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_MOVER_TALLER, "tal", needsValue, "makes cyclic movement taller (1) or shorter (0)");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_MOVER_FASTER, "fas", needsValue, "makes cyclic movement faster (1) or slower (0)");
    listCommands.push_back(oCommand);
}

bool CyclicCategory::isValidAction(int value)
{
    return (value > CyclicCategory::eCYCLIC_UNDEF && value < CyclicCategory::eCYCLIC_DIM);
}

}