/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include "amy/coms/AmyCommand.h"

namespace amy
{

AmyCommand::AmyCommand()
{
    reset();
}

/*! resets arm command values */
void AmyCommand::reset()
{
    action = eACT_UNDEFINED;    
    target = eTAR_UNDEFINED;
    value = 0.0;
    text = "";
}

bool AmyCommand::buildCommand(int action, int target, float value)
{
    bool bvalid = (action > eACT_UNDEFINED && action < eACT_DIM) && 
                        (target > eTAR_UNDEFINED && target < eTAR_DIM);
    
    if (bvalid) 
    {
        this->action = action;
        this->target = target;
        this->value = value;
        text = std::to_string(action) + separator + std::to_string(target) + separator + std::to_string(value);
    }
    
    return bvalid;
}

// split text into tokens and interpret them
bool AmyCommand::interpret(std::string text)
{
    bool bvalid = true;
    this->text = text;    
    std::vector<std::string> listTokens; 

    // split text in tokens (separated by *)
    std::string::size_type orig = 0;
    std::string::size_type pos;
    bool bdone = false;    
    while (!bdone)
    {
        // search separator
        pos = text.find_first_of(separator, orig);
        
         // if found, get token
        if (pos != std::string::npos)
            listTokens.push_back(text.substr(orig, pos-orig));
        // otherwise, get last token
        else
        {
            listTokens.push_back(text.substr(orig, pos-orig));
            bdone = true; 
        }
        
        orig = pos+1;
    }

    // fist token has the action
    action = std::stoi(listTokens.at(0));
    if (action <= eACT_UNDEFINED || action >= eACT_DIM)
    {
        action = eACT_UNDEFINED;
        bvalid = false;
    }
    
    // second token has the target
    target = std::stoi(listTokens.at(1));
    if (target <= eTAR_UNDEFINED || target >= eTAR_DIM)
    {
        target = eTAR_UNDEFINED;
        bvalid = false;
    }
    
    // third token has the value
    if (listTokens.size() > 2)
    {
        value = std::stof(listTokens.at(2));
    }
                
    return bvalid;
}


bool AmyCommand::isArmCommand()
{
    bool bfound = false;
    
    switch (action)
    {
        case eACT_MOVE_ARM:
            bfound = true;
            break;
    }
    return bfound;
}

bool AmyCommand::isJointCommand()
{
    bool bfound = false;
    
    switch (action)
    {
        case eACT_MOVE_JOINT:
            bfound = true;
            break;
    }
    return bfound;
}

bool AmyCommand::isAmyCommand()
{
    bool bfound = false;
    
    switch (action)
    {
        case eACT_END_AMY:
            bfound = true;
            break;
    }
    return bfound;
}

std::string AmyCommand::describeAction(int value)
{
    std::string desc;
    switch (value)
    {
        case eACT_MOVE_ARM:
            desc = "mov";
            break;
        case eACT_MOVE_JOINT:
            desc = "pos";
            break;
        case eACT_END_AMY:
            desc = "end";
            break;
        default:
            desc = "unknown";           
    }
    
    return desc;    
}

std::string AmyCommand::describeTarget(int value)
{
    std::string desc;
    switch (value)
    {
        case eTAR_PAN:
            desc = "pan";
            break;
        case eTAR_TILT:
            desc = "tilt";
            break;
        case eTAR_RADIUS:
            desc = "end";
            break;
        case eTAR_JOINT_HSHOULDER:
            desc = "HS";
            break;
        case eTAR_JOINT_VSHOULDER:
            desc = "VS";
            break;
        case eTAR_JOINT_ELBOW:
            desc = "ELB";
            break;
        case eTAR_JOINT_VWRIST:
            desc = "WRIST";
            break;
        default:
            desc = "unknown";           
    }
    
    return desc;    
}

}