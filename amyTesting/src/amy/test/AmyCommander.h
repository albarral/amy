#ifndef __AMY_TEST_CONSOLECOMMANDER_H
#define __AMY_TEST_CONSOLECOMMANDER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/test/Interpreter.h"
#include <amy/utils/module2.h>
//#include "amy/coms/file/AmyFileClient.h"
#include "amy/coms/zero/AmyZeroMQClient.h"

namespace amy
{
// This module allows direct control of the arm from the command line.
// The module continuously listens to the command line interpreting user entered commands.
// Then sends requests to the amy process through a proper amy coms client.
class AmyCommander : public Module2
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    // logic
    std::string entry;                  // command read from console
    Interpreter oInterpreter;       // interpreter of console commands
    //AmyFileClient oAmyFileClient;     // amy client   
    AmyZeroMQClient oAmyZeroMQClient;

public:
    AmyCommander();
    //~ConsoleCommander();

    // module params
    virtual void init();        
    // ask the module to stop
    void stop();
        
private:
    void first();
    // executes the behaviour
    void loop ();
    
    // listen for user's input from console
    bool listen();
    // sends command to amy process
    void sendCommand(int action, float value);
        
    void showCommandsList();
};
}		
#endif
