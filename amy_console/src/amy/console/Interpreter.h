#ifndef __AMY_CONSOLE_INTERPRETER_H
#define __AMY_CONSOLE_INTERPRETER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "amy/console/UserCommand.h"

namespace amy
{
// This class interprets user entered commands and converts them into proper client commands for amy.
class Interpreter 
{
public:
    /*! command identifiers */
    enum eCommands
    {
         // joint positions 
         eCMD_MOVE_HS,                      /*! move horizontal shoulder */
         eCMD_MOVE_VS,                      /*! move vertical shoulder */
         eCMD_MOVE_ELB,                    /*! move elbow */
         eCMD_MOVE_VWRI,                  /*! move vertical wrist */
         eCMD_MOVE_HWRI,                  /*! move horizontal wrist */
         // axis positions 
         eCMD_PAN_POS,                   /*! move arm pan to given pos*/    
         eCMD_TILT_POS,                    /*! move arm tilt to given pos*/
         eCMD_RADIUS_POS,              /*! move arm to given pos radius */  
         eCMD_KEEP_TILT,                 /*! keep arm tilt in extension movements*/    
         // axis speeds
         eCMD_PAN_SPEED,                 /*! move arm pan at given speed*/    
         eCMD_TILT_SPEED,                /*! move arm tilt at given speed*/
         eCMD_RADIAL_SPEED,            /*! move arm radius at given speed*/  
         // arm commands
         eCMD_ARM_STOP,                 /*! stop arm */
         eCMD_AMY_END                     /*! end amy */                    
    };
    
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
    int action;         // command code
    float value;        // command value (mandatory for complex commands)
    // arm commands
    std::vector<UserCommand> listCommands;       

public:
    Interpreter();
    //~Interpreter();
    
    // analyzes the textual input (composed by 2 strings)
    void checkCommand(std::string entry1, std::string entry2);
    // checks if this command is valid
    bool isValidCommand() {return (state == eSTATE_OK_VALID);} ;    

    int getAction() {return action;};
    float getValue() {return value;};
    int getState() {return state;};
    // get result of the check
    std::string getResult();    
    // returns list of command names and their descriptions
    std::string getAvailableCommands();    

private:    
    // build commands list
    void buildListCommands();
    // checks if given text is a number
    bool isNumeric(std::string input, int& val);    

};
}		
#endif
