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
public:
    AxisCommand(int action, float value);

};
}
#endif
