#ifndef __AMY_COMS_CYCLICCOMMAND_H
#define __AMY_COMS_CYCLICCOMMAND_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "amy/coms/data/AmyCommand.h"

namespace amy
{
 // Class to represent cyclic commands.
class CyclicCommand: public AmyCommand
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
    
public:
    CyclicCommand(int action, float value=0.0);

    // describe action 
    virtual std::string describeAction();
};
}
#endif
