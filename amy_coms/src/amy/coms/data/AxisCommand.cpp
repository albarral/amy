/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/coms/data/AxisCommand.h"

namespace amy
{

AxisCommand::AxisCommand(int action, float value)
{
    category = AmyCommand::eCAT_AXIS_CMD;
    this->action = action;
    this->value = value;
    // check command validity
    bvalid = (action > eAXIS_UNDEF && action < eAXIS_DIM);
}

std::string AxisCommand::describeAction()
{
    std::string desc;
    switch (action)
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

}