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
    category = eCAT_UNDEF;    
    action = eJOINT_UNDEF;
    value = 0.0;
    text = "";
}

bool AmyCommand::buildCommand(int category, int action, float value)
{
    // check if category and action are valid values
    bool bvalid = isValidCategory(category) && isValidAction(category, action);
    
    if (bvalid) 
    {
        this->category = category;
        this->action = action;
        this->value = value;
        // the textual command is built by 3 numbers separated by the "*" character
        text = std::to_string(category) + separator + std::to_string(action) + separator + std::to_string(value);
//        text = describeCategory(category) + separator + describeAction(category, action) + separator + std::to_string(value);
    }
    
    return bvalid;
}

// split text into tokens and interpret them
bool AmyCommand::interpret(std::string text)
{
    bool bvalid = true;
    bool bnumeric;
    this->text = text;    
    
    // split text in tokens (separated by *)
    std::vector<std::string> listTokens = StringUtil::split(text, separator); 

    // check the category (first element, int)
    bnumeric = StringUtil::convert2Integer(listTokens.at(0), category);
    // if well converted, check its validity
    bvalid = bnumeric && isValidCategory(category);
    // if not valid, undefined
    if (!bvalid)
        category = eCAT_UNDEF;

    // if valid category
    if (bvalid)
    {
        // check the action (second element, int)
        bnumeric = StringUtil::convert2Integer(listTokens.at(1), action);
        // if well converted, check its validity
        bvalid = bnumeric && isValidAction(category, action);
        // if not valid, undefined
        if (!bvalid)
            action = eJOINT_UNDEF;
    }

    // if valid action
    if (bvalid)
    {
        // check the value (third element, float)
        if (listTokens.size() > 2)
        {
            bvalid = StringUtil::convert2Float(listTokens.at(2), value);
        }
    }
    
    return bvalid;
}

bool AmyCommand::isValidCategory(int cat)
{
    return (cat > eCAT_UNDEF && cat < eCAT_DIM);    
}

bool AmyCommand::isValidAction(int cat, int value)
{
    bool bvalid; 
    switch (cat)
    {
        case eCAT_JOINT_CMD:
            bvalid = isValidJointAction(value);
            break;
        case eCAT_AXIS_CMD:
             bvalid = isValidAxisAction(value);
            break;
        case eCAT_ARM_CMD:
             bvalid = isValidArmAction(value);
            break;
        case eCAT_AMY_CMD:
             bvalid = isValidAmyAction(value);
            break;
        default:
             bvalid = false;
    }
    return bvalid;
}

bool AmyCommand::isValidJointAction(int value)
{
    return (value > eJOINT_UNDEF && value < eJOINT_DIM);    
}

bool AmyCommand::isValidAxisAction(int value)
{
    return (value > eAXIS_UNDEF && value < eAXIS_DIM);    
}

bool AmyCommand::isValidArmAction(int value)
{
    return (value > eARM_UNDEF && value < eARM_DIM);    
}

bool AmyCommand::isValidAmyAction(int value)
{
    return (value > eAMY_UNDEF && value < eAMY_DIM);    
}
    
std::string AmyCommand::getDescription()
{
    std::string desc = describeCategory(category) + 
            " " + describeAction(category, action) + 
            " " + std::to_string(value);
    
    return desc;    
}

std::string AmyCommand::describeCategory(int value)
{
    std::string desc;
    switch (value)
    {
        case eCAT_JOINT_CMD:
            desc = "joint";
            break;
        case eCAT_AXIS_CMD:
            desc = "axis";
            break;
        case eCAT_ARM_CMD:
            desc = "arm";
            break;
        case eCAT_AMY_CMD:
            desc = "amy";
            break;
        default:
            desc = "unknown";           
    }
    
    return desc;    
}

std::string AmyCommand::describeAction(int cat, int value)
{
    std::string desc;
    switch (cat)
    {
        case eCAT_JOINT_CMD:
            desc = describeJointAction(value);
            break;
        case eCAT_AXIS_CMD:
            desc = describeAxisAction(value);
            break;
        case eCAT_ARM_CMD:
            desc = describeArmAction(value);
            break;
        case eCAT_AMY_CMD:
            desc = describeAmyAction(value);
            break;
        default:
            desc = "unknown";           
    }    
    return desc;    
}

std::string AmyCommand::describeJointAction(int value)
{
    std::string desc;
    switch (value)
    {
        case eJOINT_HS_POS:
            desc = "hs pos";
            break;
        case eJOINT_VS_POS:
            desc = "vs pos";
            break;
        case eJOINT_ELB_POS:
            desc = "elb pos";
            break;
        case eJOINT_HWRI_POS:
            desc = "hwri pos";
            break;
        case eJOINT_VWRI_POS:
            desc = "vwri pos";
            break;
        default:
            desc = "unknown";           
    }   
    return desc;    
}

std::string AmyCommand::describeAxisAction(int value)
{
    std::string desc;
    switch (value)
    {
        case eAXIS_PAN_POS:
            desc = "pan pos";
            break;
        case eAXIS_TILT_POS:
            desc = "tilt pos";
            break;
        case eAXIS_RAD_POS:
            desc = "radius pos";
            break;
        case eAXIS_PAN_SPEED:
            desc = "pan speed";
            break;
        case eAXIS_TILT_SPEED:
            desc = "tilt speed";
            break;
        case eAXIS_RAD_SPEED:
            desc = "radius speed";
            break;
        default:
            desc = "unknown";           
    }    
    return desc;    
}

std::string AmyCommand::describeArmAction(int value)
{
    std::string desc;
    switch (value)
    {
        case eARM_STOP:
            desc = "stop";
            break;
        case eARM_KEEP_TILT:
            desc = "keep tilt";
            break;
        default:
            desc = "unknown";           
    }    
    return desc;    
}

std::string AmyCommand::describeAmyAction(int value)
{
    std::string desc;
    switch (value)
    {
        case eAMY_END:
            desc = "end";
            break;
        default:
            desc = "unknown";           
    }    
    return desc;    
}

}