/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/data/Joint.h"

namespace amy
{
Joint::Joint ()
{
    benabled = false;
}

Joint::~Joint()
{
}

void Joint::init(ParamsJoint& oParamsJoint)
{
    // control proper argument values
//    if (type < 0 || type >= eJOINT_INVALID ||        
    if (oParamsJoint.getLimit1() >= oParamsJoint.getLimit2())
        return;

    name = oParamsJoint.getJointName();
    limit1 = oParamsJoint.getLimit1();
    limit2 = oParamsJoint.getLimit2();
    rest = 0; // default
    benabled = true;
};

}
