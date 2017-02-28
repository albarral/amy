/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include<iostream>
#include <string>

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "amy/console/Interpreter.h"

void showUsage();

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("amy.console"));

// main program
int main(int argc, char** argv) 
{       
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
    
    // command with wrong number of params, show usage
    if (argc == 1 || argc > 3)
    {
        showUsage();
    }
    // command with proper params number
    else         
    {
        /// read command
        std::string param1 = argv[1];               // first param read from console
        std::string param2 = "";                      // second param read from console
        if (argc == 3)
           param2 = argv[2];
           
        // interpret command
        amy::Interpreter oInterpreter;
        oInterpreter.checkCommand(param1, param2);
        
        if (oInterpreter.isValidCommand())
        {
            LOG4CXX_INFO(logger, "ok: " << oInterpreter.getAction());            
        }
        else
        {
            std::string result = oInterpreter.getResult();
            LOG4CXX_ERROR(logger, param1 << ": " << result);                        
        }                
    }
    
    return 0;
}

void showUsage()
{
    LOG4CXX_INFO(logger, "usage: amyc <action> [<value>]");        

    amy::Interpreter oInterpreter;
    std::string description = oInterpreter.getAvailableCommands();
    LOG4CXX_INFO(logger, "\nThe available actions are:\n" << description);
}

