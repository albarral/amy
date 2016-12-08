#ifndef __AMY_TEST_INTERPRETER_H
#define __AMY_TEST_INTERPRETER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

namespace amy
{
// This class is used to interpret and convert textual inputs into amy coms commands.
// Commands involve two parts: an action and a value.
// A command is complete when both parts have been defined.
class Interpreter 
{
public:
    /*! action identifiers */
    enum eAction
    {
         eACT_INVALID,                      /*! invalid action */
         eACT_MOVE_PAN,                 /*! move arm pan */    
         eACT_MOVE_TILT,                /*! move arm tilt */
         eACT_MOVE_RADIUS,            /*! move arm radius */  
         eACT_ARM_STOP,                 /*! stop arm */
         eACT_POS_HS,                      /*! move horizontal shoulder */
         eACT_POS_VS,                      /*! move vertical shoulder */
         eACT_POS_ELB,                      /*! move elbow */
         eACT_POS_VWRI,                      /*! move vertical wrist */
         eACT_POS_HWRI,                     /*! move horizontal wrist */
         eACT_AMY_END                       /*! end amy */                    
    };

private:
    enum eMode
    {
         eMODE_TEXTUAL,     // waits for text input
         eMODE_NUMERIC      // waits for numeric input
    };        
    int mode;               // textual or numeric (eMode)
    int action; 
    float value;
    bool bcomplete;       // indicates the command is complete (has action & value)
    // arm input commands
    std::string movePan;              // command to move arm's pan
    std::string moveTilt;               // command to move arm's tilt
    std::string moveRadius;         // command to move arm's extension 
    std::string armStop;              // command to stop arm
    // joint input commands
    std::string moveHS;               // command to move HS joint               
    std::string moveVS;                // command to move VS joint 
    std::string moveELB;               // command to move ELB joint
    std::string moveVWRI;                 // command to move vertical wrist 
    std::string moveHWRI;              // command to move horizontal wrist 
    // amy process input commands
    std::string amyEnd;                 // command to stop amy process

public:
    Interpreter();
    //~Interpreter();
    
    // analyzes the textual input
    void checkCommand(std::string input);
    // checks if this command is valid
    bool isCommandValid() {return (action != eACT_INVALID);} ;    
    // checks if command is complete
    bool isCommandComplete() {return bcomplete;};

    int getAction() {return action;};
    float getValue() {return value;};

    // return list of valid arm commands
    std::vector<std::string> getArmCommands();
    // return list of valid joint commands
    std::vector<std::string> getJointCommands();
    // return list of valid amy process commands
    std::vector<std::string> getAmyCommands();

private:    
    // checks if given text is a number
    bool isNumeric(std::string input, int& val);    

    // checks if entered command is an arm movement
    bool checkArmCommand(std::string input);
    // checks if entered command is a joint movement one 
    bool checkJointCommand(std::string input);    
    // checks if entered command is an amy process command
    bool checkAmyCommand(std::string input);    


};
}		
#endif
