/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/data/AmyCommand.h"
#include "amy/coms/dictionary/ComsCategory.h"
#include "amy/utils/StringUtil.h"

namespace amy
{
const std::string AmyCommand::separator = "*";

AmyCommand::AmyCommand()
{
    category = ComsCategory::eCATEGORY_UNDEF;
    action = 0;
    value = 0.0;
    text = "";
    bvalid = false;
}

AmyCommand::AmyCommand(int action, float value)
{
    // undefined category, invalid command
    category = ComsCategory::eCATEGORY_UNDEF;
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
    
std::string AmyCommand::describeAction()
{
    return "invalid";    
}

}