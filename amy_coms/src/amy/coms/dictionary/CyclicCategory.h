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
         eCYCLIC_PAN_FREQ,
         eCYCLIC_PAN_AMP,
         eCYCLIC_PAN_TRIGGER,
         eCYCLIC_PAN_STOP,
         eCYCLIC_DIM
    };

    CyclicCategory(); 

 private:    
    // builds category with a list of commands
    virtual void build();
};
}
#endif
