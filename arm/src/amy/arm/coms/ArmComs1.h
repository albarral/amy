#ifndef __AMY_ARMCOMS1_H
#define __AMY_ARMCOMS1_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/coms/ArmCommander.h"
#include <amy/utils/module2.h>

namespace amy
{
// This module allows direct control of the arm from the command line.
// A set of commands are available that involve the 3 modules of the arm control (ArmMover, JointMover's and JointControl's)
// The module continuously listens to the command line interpreting user entered commands.
// Then produces the corresponding movements by sending proper signals through the arm's bus.
class ArmComs1 : public Module2
{
private:
    /*! command type */
    enum eCommand
    {
         eCOM_EMPTY,            /*! empty command */
         eCOM_INVALID,            /*! invalid command (ie. number when text expected)*/    
         eCOM_UNKNOWN,        /*! unknown command (not in accepted list) */    
         eCOM_POSITION,         /*! position command */
         eCOM_MOVEMENT,      /*! movement command */
         eCOM_DIM
    };

    static log4cxx::LoggerPtr logger;
    bool benabled;
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pBus;
    // logic
    std::string entry;            // command read from console
    bool bExpectingNumber;      // waiting for numeric commands
    static const int lenSelection = 2;             //  length of joint selection commands (hs, vs, el, vw, hw)
    static const int lenCommand = 3;            //  length of other commands (for)
    int commandType;              // received command type
    bool bArmedCommand;       // indicates the command can be sent to bus  
    std::vector<std::string> listCommands;      // accepted commands
    std::vector<std::string> listDescriptions;     // description of accepted commands 
    std::string base;                      // base of a completed command 
    std::string targetJoint;             // controlled joint   
    int value;
    ArmCommander oArmCommander;
    ArmCommand oArmCommand;
    // commands
    std::string comsPan;              // command for changing the arm's pan
    std::string comsTilt;              // command for changing the arm's tilt
    std::string comsExtend;         // command for changing the arm's extension 
    std::string comsJStop;          // command for stopping a joint
    std::string comsMovement;   // command for doing predefined movements
    std::string comsEnd;            // command for stopping all arm control modules

public:
    ArmComs1 ();
    ~ArmComs1();

    // module params
    void init ();       
    bool isEnabled() {return benabled;};

    // bus connection 
    void connect(ArmBus& oBus);
    bool isConnected() {return bconnected;};
        
    // ask the module to stop
    void stop();
        
private:
    void first();
    // executes the behaviour
    void loop ();
    
    // listen for user's input (from console))
    void listen();
    // analyses the textual input
    void analyseText();
    // checks if entered command is a joint selection one
    bool checkSelectionCommand();
    // checks if entered command is a normal movement one 
    bool checkValidCommand();    
    // checks if entered command needs a number to be completed
    bool checkNeedsCompletion();    
    // checks if given text is a number
    bool checkNumericValue(std::string input);
    
    // builds a movement command for the bus
    bool buildMovementCommand();
    // builds a joint position command for the bus
    bool buildPositionCommand();
    // sends built command through the bus
    void sendCommand();    
        
    void showCommandsList();
};
}		
#endif
