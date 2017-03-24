/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdexcept>      // std::invalid_argument

#include "amy/console/Interpreter.h"
#include "amy/utils/StringUtil.h"


namespace amy
{
// Constructor 
Interpreter::Interpreter()
{    
    state = eCHECK_FIRST_WORD;
    
    // select the commands of amy_coms dictionary that will be analyzed by the interpreter
    std::vector<ComsCommand>& listJointCommands = oComsDictionary.getJointCategory().getListCommands();
    std::vector<ComsCommand>& listAxisCommands = oComsDictionary.getAxisCategory().getListCommands();
    std::vector<ComsCommand>& listCyclicCommands = oComsDictionary.getCyclicCategory().getListCommands();
    std::vector<ComsCommand>& listOtherCommands = oComsDictionary.getOtherCategory().getListCommands();
    listCommands.insert(listCommands.end(), listJointCommands.begin(), listJointCommands.end());
    listCommands.insert(listCommands.end(), listAxisCommands.begin(), listAxisCommands.end());
    listCommands.insert(listCommands.end(), listCyclicCommands.begin(), listCyclicCommands.end());
    listCommands.insert(listCommands.end(), listOtherCommands.begin(), listOtherCommands.end());
}

void Interpreter::checkCommand(std::string entry1, std::string entry2)
{  
    // the check will go through a set of states 
    state = eCHECK_FIRST_WORD;
    // search command in commands list
    for (ComsCommand& oCommand : listCommands)
    {
        // if found, take note and skip search
        if (entry1.compare(oCommand.getName()) == 0)
        {
            category = oCommand.getCategory();
            action = oCommand.getID();
            // if simple command -> valid
            if (oCommand.getNumElements() == 0)
                state = eCHECK_VALID_CMD;
            // if complex command -> check second part
            else
                state = eCHECK_SECOND_WORD;
            break;
        }        
    }

    // if not found -> unknown
    if (state == eCHECK_FIRST_WORD)
        state = eCHECK_UNKNOWN_CMD;
        
    // nothing more to check, skip
    if (state != eCHECK_SECOND_WORD)
        return;

    // It's a complex command. Let's check the second part  ...

    // if no second part -> incomplete
    if (entry2.empty())
    {
        state = eCHECK_INCOMPLETE_CMD;
        return;            
    }

    // if second part is numeric value -> valid
    if (checkNumericParam(entry2))
        state = eCHECK_VALID_CMD;        
    // otherwise -> invalid
    else
        state = eCHECK_INVALID_CMD;
}

// checks if the specified text is a number (integer or float)
bool Interpreter::checkNumericParam(std::string input)
{
    bool bnumeric = false;
    int ivalue;
    float fvalue;
    
    // try if it's a float 
    if (StringUtil::convert2Float(input, fvalue))
    {
        bnumeric = true;
        value = fvalue;        
    }
    // or try if it's an integer
    else if (StringUtil::convert2Integer(input, ivalue))
    {
        bnumeric = true;
        value = ivalue;
    }

    return bnumeric;
}


std::string Interpreter::getResult()
{
    std::string result;
    switch (state)
    {
        case eCHECK_UNKNOWN_CMD:
            result = "unknown command";
            break;
        case eCHECK_INCOMPLETE_CMD:
            result = "incomplete command";
            break;
        case eCHECK_INVALID_CMD:
            result = "invalid value";
            break;
        case eCHECK_VALID_CMD:
            result = "ok";
            break;            
    }    
    return result;
}

std::string Interpreter::getAvailableCommands()
{    
    std::string desc;
    for (ComsCommand& oCommand : listCommands)
    {
        desc += "\t" + oCommand.getName() + " \t \t ->  \t \t " + oCommand.getDesc() + "\n";
    }
    return desc;
}

}