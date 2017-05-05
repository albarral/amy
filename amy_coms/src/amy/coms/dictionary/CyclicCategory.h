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
         // FRONTAL CYCLER
         eCYCLIC_FRONT_FREQ,  
         eCYCLIC_FRONT_AMP,
         eCYCLIC_FRONT_ANGLE,
         eCYCLIC_FRONT_START,
         eCYCLIC_FRONT_STOP,
         // ARM MOVER
         eCYCLIC_MOVER_LAUNCH,
         eCYCLIC_MOVER_STOP,
         eCYCLIC_MOVER_TURN,
         eCYCLIC_MOVER_WIDER,
         eCYCLIC_MOVER_TALLER,
         eCYCLIC_MOVER_FASTER,
         eCYCLIC_DIM
    };

    CyclicCategory(); 

    // check if given action is valid for this category
    static bool isValidAction(int value);
    
 private:    
    // builds category with a list of commands
    virtual void build();
};
}
#endif
