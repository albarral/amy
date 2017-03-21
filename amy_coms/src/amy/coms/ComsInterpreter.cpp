/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "amy/coms/ComsInterpreter.h"
#include "amy/coms/data/JointCommand.h"
#include "amy/coms/data/AxisCommand.h"
#include "amy/coms/data/CyclicCommand.h"
#include "amy/coms/data/OtherCommand.h"
#include "amy/utils/StringUtil.h"

namespace amy
{
ComsInterpreter::ComsInterpreter()
{
    pCommand = 0;
}

ComsInterpreter::~ComsInterpreter()
{
    // clear command from heap
    if (pCommand != 0)
        delete(pCommand);
}

bool ComsInterpreter::checkCommand(std::string text)
{
    int category = 0;
    int action = 0;
    float value = 0.0;

    // first delete previous command
    if (pCommand != 0)
    {
        delete(pCommand);
        pCommand = 0;
    }
    
    // split text in tokens (separated by *)
    std::vector<std::string> listTokens = StringUtil::split(text, AmyCommand::separator); 
    int numElements = listTokens.size();
    int numValidElements = 0;

    // check the category (first element, int)
    if (numElements > 0)
    {
        if (StringUtil::convert2Integer(listTokens.at(0), category))
            numValidElements++;
    }
    
    // check the action (second element, int)
    if (numElements > 1)
    {
        if (StringUtil::convert2Integer(listTokens.at(1), action))
            numValidElements++;
    }
        
    // check the value (third element, float)
    if (numElements > 2)
    {
        if (StringUtil::convert2Float(listTokens.at(2), value))
            numValidElements++;
    }

    // if all elements valid, analyze command
    if (numElements == numValidElements)
    {
        if (AmyCommand::isValidCategory(category))
        {        
            switch (category)
            {
                case AmyCommand::eCAT_JOINT_CMD:
                    pCommand = new JointCommand(action, value);
                    break;
                case AmyCommand::eCAT_AXIS_CMD:
                    pCommand = new AxisCommand(action, value);
                    break;
                case AmyCommand::eCAT_CYCLIC_CMD:
                     pCommand = new CyclicCommand(action, value);
                    break;
                case AmyCommand::eCAT_OTHER_CMD:
                     pCommand = new OtherCommand(action, value);
                    break;
            }
        }    
        // if not valid, undefined command
        else
            pCommand = new AmyCommand(action, value);
    }
    
    // returns true if a command was obtained (valid or undefined)
    return (pCommand != 0);
}

}