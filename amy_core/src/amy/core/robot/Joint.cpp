/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/core/robot/Joint.h"

namespace amy
{
const std::string Joint::hshoulder = "hs";
const std::string Joint::vshoulder = "vs";
const std::string Joint::elbow = "el";
const std::string Joint::hwrist = "hw";
const std::string Joint::vwrist = "vw";

Joint::Joint ()
{
    type = -1;
    name = "joint";
    limit1 = limit2 = 0;
}

Joint::~Joint()
{
}

void Joint::setType(int value)
{
    // safety check
    if (isValidType(value))
    {
        type = value;
        name = Joint::getName4Type(type);
    }    
}

void Joint::setLimits(int lowLimit, int highLimit)
{
    // ignore unproper limits
    if (lowLimit >= highLimit)
        return;

    limit1 = lowLimit;
    limit2 = highLimit;
}

bool Joint::isValidType(int value)
{
    return (value >= 0 && value < Joint::eJOINT_DIM);
}

std::string Joint::getName4Type(int type)
{
    switch (type)
    {
        case Joint::eJOINT_HS:
            return Joint::hshoulder;
            break;
        case Joint::eJOINT_VS:
            return Joint::vshoulder;
            break;
        case Joint::eJOINT_ELB:
            return Joint::elbow;
            break;
        case Joint::eJOINT_HW:
            return Joint::hwrist;
            break;
        case Joint::eJOINT_VW:
            return Joint::vwrist;
            break;
        default:
            return "";
    }
}

std::string Joint::toString()
{
    return "Joint: " + std::to_string(type) + " - " + name + ", limits=(" + std::to_string(limit1) + ", " + std::to_string(limit2) + ")";
}

}
