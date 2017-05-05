#ifndef __AMY_COMS_OTHERCATEGORY_H
#define __AMY_COMS_OTHERCATEGORY_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/dictionary/ComsCategory.h"

namespace amy
{
// Class used to hold all communication commands of other categories .
 class OtherCategory: public ComsCategory
{
public:
    /*! actions of other category  */
    enum eOtherActions
    {
         eOTHER_UNDEF,                       /*! undefined action */
         eOTHER_ARM_STOP,                 /*! stop arm */
         eOTHER_KEEP_TILT,                  /*! keep the tilt position */
         eOTHER_AMY_END,                   /*! end amy */
         eOTHER_DIM
    };

    OtherCategory(); 

    // check if given action is valid for this category
    static bool isValidAction(int value);

 private:    
    // builds category with a list of commands
    virtual void build();
};
}
#endif
