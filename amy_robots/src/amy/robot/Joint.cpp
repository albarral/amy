/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/robot/Joint.h"

namespace amy
{
Joint::Joint ()
{
    name = "joint";
    limit1 = limit2 = 0;
}

Joint::~Joint()
{
}

void Joint::setLimits(int lowLimit, int highLimit)
{
    // ignore unproper limits
    if (lowLimit >= highLimit)
        return;

    limit1 = lowLimit;
    limit2 = highLimit;
};

}