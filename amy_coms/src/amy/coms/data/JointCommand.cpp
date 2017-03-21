/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/coms/data/JointCommand.h"

namespace amy
{

JointCommand::JointCommand(int action, float value)
{
    category = AmyCommand::eCAT_JOINT_CMD;
    this->action = action;
    this->value = value;
    // check command validity
    bvalid = (action > eJOINT_UNDEF && action < eJOINT_DIM);
}

std::string JointCommand::describeAction()
{
    std::string desc;
    switch (action)
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

}