/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "amy/coms/data/AmyCommand.h"
#include "amy/utils/StringUtil.h"

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
        // the command is composed by 3 numbers separated by the "*" character
        text = std::to_string(action) + separator + std::to_string(target) + separator + std::to_string(value);
//        text = describeAction(action) + separator + describeTarget(target) + separator + std::to_string(value);
    }
    
    return bvalid;
}

// split text into tokens and interpret them
bool AmyCommand::interpret(std::string text)
{
    bool bvalid = true;
    this->text = text;    
    
    // split text in tokens (separated by *)
    std::vector<std::string> listTokens = StringUtil::split(text, separator); 

    /*
    try
    {
        // first token has the action
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
    }
    catch (std::invalid_argument) 
    {
        // if any token is not numeric the command is invalid
        bvalid = false;        
    }
     */ 

    // first token has the action (int)
    bvalid = StringUtil::convert2Integer(listTokens.at(0), action);
    // if well converted, check its range
    if (bvalid && (action <= eACT_UNDEFINED || action >= eACT_DIM))
    {
        action = eACT_UNDEFINED;
        bvalid = false;
    }

    if (bvalid)
    {
        // second token has the target (int)
        bvalid = StringUtil::convert2Integer(listTokens.at(1), target);
        // if well converted, check its range
        if (bvalid && (target <= eTAR_UNDEFINED || target >= eTAR_DIM))
        {
            target = eTAR_UNDEFINED;
            bvalid = false;
        }
    }

    if (bvalid)
    {
        // third token has the value (float)
        if (listTokens.size() > 2)
        {
            bvalid = StringUtil::convert2Float(listTokens.at(2), value);
        }
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

std::string AmyCommand::getDescription()
{
    std::string desc = describeAction(action) + 
            " " + describeTarget(target) + 
            " " + std::to_string(value);
    
    return desc;    
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
            desc = "radius";
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
        case eTAR_JOINT_HWRIST:
            desc = "HWRIST";
            break;
        case eTAR_JOINT_VWRIST:
            desc = "VWRIST";
            break;
        case eTAR_PROGRAM:
            desc = "program";
            break;
        default:
            desc = "unknown";           
    }
    
    return desc;    
}

}