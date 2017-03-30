/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/dictionary/ComsDictionary.h"

namespace amy
{

std::string ComsDictionary::toString()
{
    std::string desc = "ComsDictionary: \n" + 
            oJointCategory.toString() + 
            oAxisCategory.toString() + 
            oCyclicCategory.toString() +
            oOtherCategory.toString();

    return desc;    
}

std::string ComsDictionary::describeAction4Category(int cat, int action)
{
    std::string desc;
    switch (cat)
    {
        case ComsCategory::eCATEGORY_UNDEF:
            desc = "undefined category";
            break;
        case ComsCategory::eCATEGORY_JOINTS:
            desc = JointCategory::describeAction(action);
            break;
        case ComsCategory::eCATEGORY_AXIS:
            desc = AxisCategory::describeAction(action);
            break;
        case ComsCategory::eCATEGORY_CYCLIC:
            desc = CyclicCategory::describeAction(action);
            break;
        case ComsCategory::eCATEGORY_OTHER:
            desc = OtherCategory::describeAction(action);
            break;            
        default:
            desc = "invalid category";           
    }
    return desc;    
}

}