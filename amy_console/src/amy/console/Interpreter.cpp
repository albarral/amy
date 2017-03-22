/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdexcept>      // std::invalid_argument

#include "amy/console/Interpreter.h"


namespace amy
{
// Constructor 
Interpreter::Interpreter()
{    
    state = eSTATE_CHECK_FIRST;
    
    // build the list of available commands from the coms dictionary (all categories)      
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
    // not valid till correctly checked
    state = eSTATE_CHECK_FIRST;
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
                state = eSTATE_OK_VALID;
            // if complex command -> check second part
            else
                state = eSTATE_CHECK_SECOND;
            break;
        }        
    }

    // if not found -> unknown
    if (state == eSTATE_CHECK_FIRST)
        state = eSTATE_KO_UNKNOWN;
        
    // nothing more to check, skip
    if (state != eSTATE_CHECK_SECOND)
        return;

    // It's a complex command. Let's check the second part  ...

    // if no second part -> incomplete
    if (entry2.empty())
    {
        state = eSTATE_KO_INCOMPLETE;
        return;            
    }

    // if second part is numeric value -> valid
    int x;
    if (isNumeric(entry2, x))
    {
        value = (float)x;
        state = eSTATE_OK_VALID;        
    }
    // otherwise -> invalid
    else
        state = eSTATE_KO_INVALID;

}

// checks if the specified text is a number
bool Interpreter::isNumeric(std::string input, int& val)
{
    try
    {
        // try converting string to integer
        val = std::stoi(input);
        return true;
    }
    catch (std::invalid_argument) 
    {
        // if conversion fails it's not a number
        return false;        
    }
}

std::string Interpreter::getResult()
{
    std::string result;
    switch (state)
    {
        case eSTATE_KO_UNKNOWN:
            result = "unknown command";
            break;
        case eSTATE_KO_INCOMPLETE:
            result = "incomplete command";
            break;
        case eSTATE_KO_INVALID:
            result = "invalid value";
            break;
        case eSTATE_OK_VALID:
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