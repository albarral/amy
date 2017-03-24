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
         eCHECK_FIRST_WORD,              /*! checking: first part (action) */
         eCHECK_SECOND_WORD,          /*! checking: second part (value) */
         eCHECK_UNKNOWN_CMD,         /*! check ko: unknown command */
         eCHECK_INCOMPLETE_CMD,          /*! check ko: incomplete command */
         eCHECK_INVALID_CMD,                 /*! check ko: invalid command */
         eCHECK_VALID_CMD,                    /*! check ok: valid command */
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
    bool isValidCommand() {return (state == eCHECK_VALID_CMD);} ;    

    int getCategory() {return category;};
    int getAction() {return action;};
    float getValue() {return value;};
    int getState() {return state;};
    // get result of the check
    std::string getResult();    
    // returns list of command names and their descriptions
    std::string getAvailableCommands();    

private:    
    // checks if given text is a number (integer or float)
    bool checkNumericParam(std::string input);    

};
}		
#endif
