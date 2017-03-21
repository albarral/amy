/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/coms/data/OtherCommand.h"

namespace amy
{

OtherCommand::OtherCommand(int action, float value)
{
    category = AmyCommand::eCAT_OTHER_CMD;
    this->action = action;
    this->value = value;
    // check command validity
    bvalid = (action > eOTHER_UNDEF && action < eOTHER_DIM);
}


std::string OtherCommand::describeAction()
{
    std::string desc;
    switch (action)
    {
        case eOTHER_ARM_STOP:
            desc = "stop";
            break;
        case eOTHER_KEEP_TILT:
            desc = "keep tilt";
            break;
        case eOTHER_AMY_END:
            desc = "end";
            break;
        default:
            desc = "unknown";           
    }    
    return desc;    
}

}