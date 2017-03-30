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
    
    // define commands for pan cyclic movements
    ComsCommand oCommand(ID, CyclicCategory::eCYCLIC_PAN_FREQ, "panf", 1, "set frequency of pan cycles (Hz)");    
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_PAN_AMP, "pana", 1, "set amplitude of pan cycles (degrees)");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_PAN_TRIGGER, "pan1", 0, "trigger pan cyclic movement");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_PAN_STOP, "pan0", 0, "stop pan cyclic movement");
    listCommands.push_back(oCommand);
    // define commands for tilt cyclic movements
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_TILT_FREQ, "tiltf", 1, "set frequency of tilt cycles (Hz)");    
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_TILT_AMP, "tilta", 1, "set amplitude of tilt cycles (degrees)");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_TILT_TRIGGER, "tilt1", 0, "trigger tilt cyclic movement");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_TILT_STOP, "tilt0", 0, "stop tilt cyclic movement");
    listCommands.push_back(oCommand);
}

bool CyclicCategory::isValidAction(int value)
{
    return (value > CyclicCategory::eCYCLIC_UNDEF && value < CyclicCategory::eCYCLIC_DIM);
}

std::string CyclicCategory::describeAction(int value)
{
    std::string desc;
    switch (value)
    {
        case CyclicCategory::eCYCLIC_PAN_FREQ:
            desc = "pan frequency";
            break;
        case CyclicCategory::eCYCLIC_PAN_AMP:
            desc = "pan amplitude";
            break;
        case CyclicCategory::eCYCLIC_PAN_TRIGGER:
            desc = "pan trigger";
            break;
        case CyclicCategory::eCYCLIC_PAN_STOP:
            desc = "pan stop";
            break;
        case CyclicCategory::eCYCLIC_TILT_FREQ:
            desc = "tilt frequency";
            break;
        case CyclicCategory::eCYCLIC_TILT_AMP:
            desc = "tilt amplitude";
            break;
        case CyclicCategory::eCYCLIC_TILT_TRIGGER:
            desc = "tilt trigger";
            break;
        case CyclicCategory::eCYCLIC_TILT_STOP:
            desc = "tilt stop";
            break;
        default:
            desc = "unknown";           
    }    
    return desc;    
}

}