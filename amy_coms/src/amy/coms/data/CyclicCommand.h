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
    CyclicCommand(int action, float value=0.0);

};
}
#endif
