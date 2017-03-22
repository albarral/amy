#ifndef __AMY_CONSOLE_INTERPRETER_H
#define __AMY_CONSOLE_INTERPRETER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "amy/coms/dictionary/ComsCommand.h"
#include "amy/coms/dictionary/ComsDictionary.h"

namespace amy
{
// This class interprets user entered commands and converts them into proper client commands for amy.
class Interpreter 
{
private:
    /*! interpreter states */        
    enum eStates
    {
         eSTATE_CHECK_FIRST,              /*! checking: first part (action) */
         eSTATE_CHECK_SECOND,          /*! checking: second part (value) */
         eSTATE_KO_UNKNOWN,              /*! check ko: unknown command */
         eSTATE_KO_INCOMPLETE,          /*! check ko: incomplete command */
         eSTATE_KO_INVALID,                 /*! check ko: invalid command */
         eSTATE_OK_VALID,                    /*! check ok: valid command */
    };
    int state;           // interpreter state (one of eStates)
    int category;     // command category      
    int action;         // command code
    float value;        // command value (mandatory for complex commands)    
    ComsDictionary oComsDictionary;  // dictionary with all coms commands available
    std::vector<ComsCommand> listCommands;    

public:
    Interpreter();
    //~Interpreter();
    
    // analyzes the textual input (composed by 2 strings)
    void checkCommand(std::string entry1, std::string entry2);
    // checks if this command is valid
    bool isValidCommand() {return (state == eSTATE_OK_VALID);} ;    

    int getCategory() {return category;};
    int getAction() {return action;};
    float getValue() {return value;};
    int getState() {return state;};
    // get result of the check
    std::string getResult();    
    // returns list of command names and their descriptions
    std::string getAvailableCommands();    

private:    
    // checks if given text is a number
    bool isNumeric(std::string input, int& val);    

};
}		
#endif
