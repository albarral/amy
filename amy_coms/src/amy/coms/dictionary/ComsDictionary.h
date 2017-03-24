#ifndef __AMY_COMS_COMSDICTIONARY_H
#define __AMY_COMS_COMSDICTIONARY_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/dictionary/JointCategory.h"
#include "amy/coms/dictionary/AxisCategory.h"
#include "amy/coms/dictionary/CyclicCategory.h"
#include "amy/coms/dictionary/OtherCategory.h"

namespace amy
{
// Class used to define all available commands to communicate with amy (divided by categories).
 class ComsDictionary
{
public:
    JointCategory oJointCategory;
    AxisCategory oAxisCategory;
    CyclicCategory oCyclicCategory;
    OtherCategory oOtherCategory;
    
public:
    //ComsDictionary();

    JointCategory& getJointCategory() {return oJointCategory;};
    AxisCategory& getAxisCategory() {return oAxisCategory;};
    CyclicCategory& getCyclicCategory() {return oCyclicCategory;};
    OtherCategory& getOtherCategory() {return oOtherCategory;};
    
    // describe dictionary
    std::string toString();
    
    // describe given action name of the given category
    static std::string describeAction4Category(int cat, int action);

};
}
#endif
