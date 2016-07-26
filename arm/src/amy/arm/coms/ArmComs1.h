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
class ArmComs1 : public Module2
{
private:
    /*! command type */
    enum eCommand
    {
         eCOM_EMPTY,            /*! empty command */
         eCOM_INVALID,            /*! invalid command */    
         eCOM_SELECTION,      /*! joint selection command */            
         eCOM_MOVEMENT,      /*! movement command */
         eCOM_POSITION,         /*! position command */
         eCOM_DIM
    };

    static log4cxx::LoggerPtr logger;
    bool benabled;
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pBus;
    // logic
    std::string entry;            // command read from console
    static const int lenSelection = 2;             //  length of joint selection commands (j1)
    static const int lenCommand = 3;            //  length of movement commands (for)
    static const int lenExtended = 4;            //  length of extended commands (arm + number)
    int commandType;            // type of command (eCommand values)
    std::vector<std::string> listCommands;      // accepted commands
    std::vector<std::string> listDescriptions;     // description of accepted commands 
    std::vector<std::string> listExtendedCommands;  // accepted extended commands
    std::vector<std::string> listExtendedDescriptions;     // description of accepted extended commands 
    int targetJoint;    // controlled joint
    std::string comsJSelection;         // command for joint selection
    std::string comsJForward;       // command for moving a joint forward
    std::string comsJBackward;    // command for moving a joint backwards
    std::string comsJBrake;         // command for braking a joint
    std::string comsJKeep;          // command for keeping a joint's speed
    std::string comsJStop;          // command for stopping a joint
    std::string comsArmMovement;   // (extended) command for launching/stopping a predefined movement
    std::string comsEnd;            // command for stopping all arm control modules
    int value;
//    bool bsendMove;           // flag indicating a movement command must be sent through the bus
//    bool bsendPosition;       // flag indicating a position command must be sent through the bus
    ArmCommander oArmCommander;
    ArmCommand oArmCommand;

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
    // checks if entered command is a joint selection one
    bool checkSelectionCommand();
    // checks if entered command is a normal movement one 
    bool checkMovementCommand();    
    // checks if entered command is an extended movement one 
    bool checkExtendedCommand();    
    // checks if given text is a number
    bool checkNumericValue(std::string input);
    
    // builds a movement command for the bus
    bool buildMovementCommand();
    // builds a joint position command for the bus
    bool buildPositionCommand();
    // sends built command through the bus
    void sendCommand();    
    
    // extract numeric suffix (last character) of a string
    int extractNumericSuffix(std::string input);
    
    void showCommandsList();
};
}		
#endif
