/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/data/CyclicCommand.h"
#include "amy/coms/dictionary/ComsCategory.h"
#include "amy/coms/dictionary/CyclicCategory.h"

namespace amy
{

CyclicCommand::CyclicCommand(int action, float value)
{
    category = ComsCategory::eCATEGORY_CYCLIC;
    this->action = action;
    this->value = value;
    // check command validity
    bvalid = CyclicCategory::isValidAction(action);
}


}