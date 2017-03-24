/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/dictionary/JointCategory.h"
#include "amy/coms/dictionary/ComsCommand.h"

namespace amy
{
JointCategory::JointCategory() : ComsCategory(eCATEGORY_JOINTS, "joints category")   
{
    // builds list of commands
    build();
}

void JointCategory::build()
{
    listCommands.clear();
    
    // define joint commands
    ComsCommand oCommand(ID, JointCategory::eJOINT_HS_POS, "hs", 1, "move horizontal shoulder joint (degrees)");    
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, JointCategory::eJOINT_VS_POS, "vs", 1, "move vertical shoulder joint (degrees)");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, JointCategory::eJOINT_ELB_POS, "elb", 1, "move elbow joint (degrees)");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, JointCategory::eJOINT_HWRI_POS, "hwri", 1, "move horizontal wrist joint (degrees)");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, JointCategory::eJOINT_VWRI_POS, "vwri", 1, "move vertical wrist joint (degrees)");
    listCommands.push_back(oCommand);
}
    
bool JointCategory::isValidAction(int value)
{
    return (value > JointCategory::eJOINT_UNDEF && value < JointCategory::eJOINT_DIM);
}

std::string JointCategory::describeAction(int value)
{
    std::string desc;
    switch (value)
    {
        case JointCategory::eJOINT_HS_POS:
            desc = "hs pos";
            break;
        case JointCategory::eJOINT_VS_POS:
            desc = "vs pos";
            break;
        case JointCategory::eJOINT_ELB_POS:
            desc = "elb pos";
            break;
        case JointCategory::eJOINT_HWRI_POS:
            desc = "hwri pos";
            break;
        case JointCategory::eJOINT_VWRI_POS:
            desc = "vwri pos";
            break;
        default:
            desc = "unknown";           
    }   
    return desc;    
}

}