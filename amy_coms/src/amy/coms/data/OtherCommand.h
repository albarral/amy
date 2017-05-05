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
 public:
    OtherCommand(int action, float value=0.0);

};
}
#endif
