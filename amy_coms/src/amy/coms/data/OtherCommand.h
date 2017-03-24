#ifndef __AMY_COMS_OTHERCOMMAND_H
#define __AMY_COMS_OTHERCOMMAND_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "amy/coms/data/AmyCommand.h"

namespace amy
{
 // Class to represent other commands (not represented in general commands)
class OtherCommand: public AmyCommand
{
//public:
//    /*! actions of other category  */
//    enum eOtherActions
//    {
//         eOTHER_UNDEF,                       /*! undefined action */
//         eOTHER_ARM_STOP,                 /*! stop arm */
//         eOTHER_KEEP_TILT,                  /*! keep the tilt position */
//         eOTHER_AMY_END,                   /*! end amy */
//         eOTHER_DIM
//    };
    
public:
    OtherCommand(int action, float value=0.0);

    // describe action 
    //virtual std::string describeAction();
};
}
#endif
