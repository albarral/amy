/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/data/JointCommand.h"
#include "amy/coms/dictionary/ComsCategory.h"
#include "amy/coms/dictionary/JointCategory.h"

namespace amy
{

JointCommand::JointCommand(int action, float value)
{
    category = ComsCategory::eCATEGORY_JOINTS;
    this->action = action;
    this->value = value;
    // check command validity
    bvalid = JointCategory::isValidAction(action);
}

}