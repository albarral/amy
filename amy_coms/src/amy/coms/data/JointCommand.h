#ifndef __AMY_COMS_JOINTCOMMAND_H
#define __AMY_COMS_JOINTCOMMAND_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/coms/data/AmyCommand.h"

namespace amy
{
// Class to represent joint commands. 
 class JointCommand : public AmyCommand
{
public:
    JointCommand(int action, float value);

};
}
#endif
