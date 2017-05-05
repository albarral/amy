#ifndef __AMY_COMS_AXISCATEGORY_H
#define __AMY_COMS_AXISCATEGORY_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/dictionary/ComsCategory.h"

namespace amy
{
// Class used to hold all communication commands of the axis category .
 class AxisCategory: public ComsCategory
{
public:
    /*! actions of axis category  */
    enum eAxisActions
    {
         eAXIS_UNDEF,                          /*! undefined axis action */
         eAXIS_PAN_POS,                       /*! pan position */
         eAXIS_TILT_POS,                       /*! tilt position */
         eAXIS_RAD_POS,                       /*! radial position */
         eAXIS_PAN_SPEED,                     /*! pan speed */
         eAXIS_TILT_SPEED,                     /*! tilt speed */
         eAXIS_RAD_SPEED,                      /*! radial speed */
         eAXIS_DIM
    };

    AxisCategory(); 

    // check if given action is valid for this category
    static bool isValidAction(int value);

 private:    
    // builds category with a list of commands
    virtual void build();
};
}
#endif
