/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/data/AmyCommand.h"
#include "amy/utils/StringUtil.h"

namespace amy
{
const std::string AmyCommand::separator = "*";

AmyCommand::AmyCommand()
{
    category = eCAT_UNDEF;    
    action = 0;
    value = 0.0;
    text = "";
    bvalid = false;
}

AmyCommand::AmyCommand(int action, float value)
{
    // undefined category, invalid command
    category = eCAT_UNDEF;
    this->action = action;
    this->value = value;
    bvalid = false;
}

std::string AmyCommand::buildTextualForm()
{
    // the textual command is built by 3 numbers (category, action and value) separated by the predefined separator (the "*" character)
    text = std::to_string(category) + separator + std::to_string(action) + separator + std::to_string(value);
    return text;
}
    
std::string AmyCommand::getDescription()
{
    std::string desc = describeCategory(category) + 
            " " + describeAction() + 
            " " + std::to_string(value);
    
    return desc;    
}

bool AmyCommand::isValidCategory(int cat)
{
    return (cat > eCAT_UNDEF && cat < eCAT_DIM);    
}

std::string AmyCommand::describeCategory(int value)
{
    std::string desc;
    switch (value)
    {
        case eCAT_UNDEF:
            desc = "undefined";
            break;
        case eCAT_JOINT_CMD:
            desc = "joint";
            break;
        case eCAT_AXIS_CMD:
            desc = "axis";
            break;
        case eCAT_CYCLIC_CMD:
            desc = "cyclic";
            break;
        case eCAT_OTHER_CMD:
            desc = "other";
            break;
        default:
            desc = "invalid";           
    }
    return desc;    
}

std::string AmyCommand::describeAction()
{
    return "invalid";    
}

}