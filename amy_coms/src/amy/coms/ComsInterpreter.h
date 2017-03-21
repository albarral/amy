#ifndef __AMY_COMS_COMSINTERPRETER_H
#define __AMY_COMS_COMSINTERPRETER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "amy/coms/data/AmyCommand.h"

namespace amy
{
/** 
 * Class used for interpretation of received commands..
 * Commands involve 3 elements: category, action and value.
 */
class ComsInterpreter
{
private:
    AmyCommand* pCommand;   // interpreted command
    
public:
    ComsInterpreter();
    ~ComsInterpreter();

    // Interpret given command. Returns true if valid.
    bool checkCommand(std::string text);
    // gets copy of interpreted command
    AmyCommand& getCommand() {return *pCommand;};
};
}
#endif
