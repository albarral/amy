/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/data/AxisCommand.h"
#include "amy/coms/dictionary/ComsCategory.h"
#include "amy/coms/dictionary/AxisCategory.h"

namespace amy
{

AxisCommand::AxisCommand(int action, float value)
{
    category = ComsCategory::eCATEGORY_AXIS;
    this->action = action;
    this->value = value;
    // check command validity
    bvalid = AxisCategory::isValidAction(action);
}

}