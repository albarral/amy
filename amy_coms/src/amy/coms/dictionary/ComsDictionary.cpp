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

}