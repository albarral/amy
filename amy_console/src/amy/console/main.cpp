/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cstdlib>  // for getenv
#include <iostream>
#include <string>

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "amy/console/Interpreter.h"
#include "amy/console/AmyConnector.h"

// shows usage of amy2
void showUsage();
// obtains user's home path
std::string getHomePath();

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("amy.console"));

// main program of amy2
int main(int argc, char** argv) 
{       
    std::string home = getHomePath();
    std::string configFile = home + "/.amy/log4cxx_config_console.xml";
    log4cxx::xml::DOMConfigurator::configure(configFile);
    
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
           
        // TEMP 
        // get input from console
//        std::string entry;
//        std::getline(std::cin, entry);   
//        std::string::size_type pos = entry.find_first_of(' ');
//        std::string param1 = entry.substr(0, pos);
//        std::string param2 = entry.substr(pos);
        
        amy::Interpreter oInterpreter;
        amy::AmyConnector oConnector;
        
        // interpret command
        oInterpreter.checkCommand(param1, param2);
        // if valid, send it to amy
        if (oInterpreter.isValidCommand())
        {
            oConnector.connect2Amy();
            bool bsent = oConnector.sendCommand(oInterpreter.getAction(), oInterpreter.getValue());
            if (!bsent)
            {
                LOG4CXX_WARN(logger, "send failed");
            }
        }
        // otherwise show why command is invalid
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
    LOG4CXX_INFO(logger, "usage: amy2 <action> [<value>]");        

    amy::Interpreter oInterpreter;
    std::string description = oInterpreter.getAvailableCommands();
    LOG4CXX_INFO(logger, "\nThe available actions are:\n" << description);
}

std::string getHomePath()
{    
    // obtain value of HOME environment variable
    char* pVar = getenv("HOME");    
    if (pVar!=NULL)
    {
        // transform it in a string
        std::string home(pVar);
        return home;
    }
    else
        return "";
}
