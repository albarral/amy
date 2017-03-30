#ifndef __AMY_COMS_AXISCOMMAND_H
#define __AMY_COMS_AXISCOMMAND_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "amy/coms/data/AmyCommand.h"

namespace amy
{
 // Class to represent axis commands.
class AxisCommand: public AmyCommand
{
//public:
//    /*! actions of axis category  */
//    enum eAxisActions
//    {
//         eAXIS_UNDEF,                          /*! undefined axis action */
//         eAXIS_PAN_POS,                       /*! pan position */
//         eAXIS_TILT_POS,                       /*! tilt position */
//         eAXIS_RAD_POS,                       /*! radial position */
//         eAXIS_PAN_SPEED,                     /*! pan speed */
//         eAXIS_TILT_SPEED,                     /*! tilt speed */
//         eAXIS_RAD_SPEED,                      /*! radial speed */
//         eAXIS_DIM
//    };
    
public:
    AxisCommand(int action, float value);

    // describe action 
    //virtual std::string describeAction();
};
}
#endif
