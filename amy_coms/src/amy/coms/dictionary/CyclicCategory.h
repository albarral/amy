#ifndef __AMY_COMS_CYCLICCATEGORY_H
#define __AMY_COMS_CYCLICCATEGORY_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/dictionary/ComsCategory.h"

namespace amy
{
// Class used to hold all communication commands of the cyclic category .
 class CyclicCategory: public ComsCategory
{
public:
    /*! actions of cyclic category  */
    enum eCyclicActions
    {
         eCYCLIC_UNDEF,                          /*! undefined cyclic action */
         eCYCLIC_FRONT_FREQ,                    // frontal movement 
         eCYCLIC_FRONT_AMP,
         eCYCLIC_FRONT_ANGLE,
         eCYCLIC_FRONT_START,
         eCYCLIC_FRONT_STOP,
//         eCYCLIC_TILT_FREQ,                      // tilt movement
//         eCYCLIC_TILT_AMP,
//         eCYCLIC_TILT_TRIGGER,
//         eCYCLIC_TILT_STOP,
         eCYCLIC_DIM
    };

    CyclicCategory(); 

    // check if given action is valid for this category
    static bool isValidAction(int value);
    // describe given action name for this category
    static std::string describeAction(int value);
    
 private:    
    // builds category with a list of commands
    virtual void build();
};
}
#endif
