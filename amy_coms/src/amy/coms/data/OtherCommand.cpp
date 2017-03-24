/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/data/OtherCommand.h"
#include "amy/coms/dictionary/ComsCategory.h"
#include "amy/coms/dictionary/OtherCategory.h"

namespace amy
{

OtherCommand::OtherCommand(int action, float value)
{
    category = ComsCategory::eCATEGORY_OTHER;
    this->action = action;
    this->value = value;
    // check command validity
    bvalid = OtherCategory::isValidAction(action);
}

}