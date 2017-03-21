/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/coms/data/CyclicCommand.h"

namespace amy
{

CyclicCommand::CyclicCommand(int action, float value)
{
    category = AmyCommand::eCAT_CYCLIC_CMD;
    this->action = action;
    this->value = value;
    // check command validity
    bvalid = (action > eCYCLIC_UNDEF && action < eCYCLIC_DIM);
}

std::string CyclicCommand::describeAction()
{
    std::string desc;
    switch (action)
    {
        case eCYCLIC_PAN_FREQ:
            desc = "pan frequency";
            break;
        case eCYCLIC_PAN_AMP:
            desc = "pan amplitude";
            break;
        case eCYCLIC_PAN_TRIGGER:
            desc = "pan trigger";
            break;
        case eCYCLIC_PAN_STOP:
            desc = "pan stop";
            break;
        default:
            desc = "unknown";           
    }    
    return desc;    
}

}