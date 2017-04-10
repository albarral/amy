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
    
    // define commands for front cyclic movements (all require an extra value)
    ComsCommand oCommand(ID, CyclicCategory::eCYCLIC_FRONT_FREQ, "freq1", 1, "set frequency of frontal cycler (Hz)");    
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_FRONT_AMP, "amp1", 1, "set amplitude of frontal cycler (degrees)");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_FRONT_ANGLE, "ang1", 1, "set orientation of frontal cycler (degrees)");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_FRONT_START, "go1", 0, "start frontal cycler movement");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_FRONT_STOP, "stop1", 0, "stop frontal cycler movement");
    listCommands.push_back(oCommand);
    // define commands for tilt cyclic movements
//    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_TILT_FREQ, "tiltf", 1, "set frequency of tilt cycles (Hz)");    
//    listCommands.push_back(oCommand);
//    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_TILT_AMP, "tilta", 1, "set amplitude of tilt cycles (degrees)");
//    listCommands.push_back(oCommand);
//    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_TILT_TRIGGER, "tilt1", 0, "trigger tilt cyclic movement");
//    listCommands.push_back(oCommand);
//    oCommand = ComsCommand(ID, CyclicCategory::eCYCLIC_TILT_STOP, "tilt0", 0, "stop tilt cyclic movement");
//    listCommands.push_back(oCommand);
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
        case CyclicCategory::eCYCLIC_FRONT_FREQ:
            desc = "front frequency";
            break;
        case CyclicCategory::eCYCLIC_FRONT_AMP:
            desc = "front amplitude";
            break;
        case CyclicCategory::eCYCLIC_FRONT_ANGLE:
            desc = "front angle";
            break;
        case CyclicCategory::eCYCLIC_FRONT_START:
            desc = "front start";
            break;
        case CyclicCategory::eCYCLIC_FRONT_STOP:
            desc = "front stop";
            break;
//        case CyclicCategory::eCYCLIC_TILT_FREQ:
//            desc = "tilt frequency";
//            break;
//        case CyclicCategory::eCYCLIC_TILT_AMP:
//            desc = "tilt amplitude";
//            break;
//        case CyclicCategory::eCYCLIC_TILT_TRIGGER:
//            desc = "tilt trigger";
//            break;
//        case CyclicCategory::eCYCLIC_TILT_STOP:
//            desc = "tilt stop";
//            break;
        default:
            desc = "unknown";           
    }    
    return desc;    
}

}