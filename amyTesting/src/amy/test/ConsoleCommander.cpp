/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream>
#include "log4cxx/ndc.h"

#include "amy/test/ConsoleCommander.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ConsoleCommander::logger(Logger::getLogger("amy.test"));

// Constructor 
ConsoleCommander::ConsoleCommander()
{    
    modName = "ConsoleCommander";
    entry = "";
 }

void ConsoleCommander::init()
{
    // nothing done    
    LOG4CXX_INFO(logger, modName << " initialized");      
};

void ConsoleCommander::first()
{    
    log4cxx::NDC::push(modName);   	
    showCommandsList();
}

void ConsoleCommander::loop()
{
    // listen to user commands
    if (listen())
    {
        // interpret command
        oInterpreter.checkCommand(entry);
        
        // if valid ...
        if (oInterpreter.isCommandValid())
        {
            // and complete, send it
            if (oInterpreter.isCommandComplete())
            {
                sendCommand(oInterpreter.getAction(), oInterpreter.getValue());                
            }
            else
                LOG4CXX_WARN(logger, "command needs a value");                    
        }
        // invalid command, skip
        else
            LOG4CXX_ERROR(logger, "Invalid command!");                    
    }
    // empty command, skip
    else 
        LOG4CXX_ERROR(logger, "Empty command!");
}


bool ConsoleCommander::listen()
{        
    LOG4CXX_INFO(logger, "> ?");    
       
    // get input from console
    std::getline(std::cin, entry);    
    // show input
    LOG4CXX_INFO(logger, "< " << entry);
          
    // return true if something entered
    return (!entry.empty());
}

// send command through the bus
void ConsoleCommander::sendCommand(int action, float value)
{
//  x  eACT_MOVE_PAN,                 /*! move arm pan */    
//  x  eACT_MOVE_TILT,                /*! move arm tilt */
//  x  eACT_MOVE_RADIUS,            /*! move arm radius */  
//    eACT_ARM_STOP,                 /*! stop arm */
//    eACT_POS_HS,                      /*! move horizontal shoulder */
//    eACT_POS_VS,                      /*! move vertical shoulder */
//    eACT_POS_ELB,                      /*! move elbow */
//    eACT_POS_VWRI,                      /*! move vertical wrist */
//    eACT_POS_HWRI,                     /*! move horizontal wrist */
//  x  eACT_AMY_END                       /*! end amy */                    

    switch (action)
    {
        case Interpreter::eACT_MOVE_PAN:            
            oAmyClient.movePan(value);
            break;

        case Interpreter::eACT_MOVE_TILT:
            oAmyClient.moveTilt(value);
            break;

        case Interpreter::eACT_MOVE_RADIUS:
            oAmyClient.moveRadius(value);
            break;

        case Interpreter::eACT_AMY_END:
            oAmyClient.endAmy();
            break;
            
        default:
            LOG4CXX_ERROR(logger, "client request not available!");                  
            break;
    }
}


void ConsoleCommander::showCommandsList()
{    
    LOG4CXX_INFO(logger, "Control the arm by using next commands (most need completion with a numeric value)");      

    std::vector<std::string> listCommands; 

    // show arm commands
    LOG4CXX_INFO(logger, "Arm commands:");      
    listCommands =  oInterpreter.getArmCommands();
    for (std::string command : listCommands)
    {
        LOG4CXX_INFO(logger, command);             
    }    

    // show joint commands
    LOG4CXX_INFO(logger, "Joint commands:");      
    listCommands =  oInterpreter.getJointCommands();
    for (std::string command : listCommands)
    {
        LOG4CXX_INFO(logger, command);             
    }    

    // show amy process commands
    LOG4CXX_INFO(logger, "Amy process commands:");      
    listCommands =  oInterpreter.getAmyCommands();
    for (std::string command : listCommands)
    {
        LOG4CXX_INFO(logger, command);             
    }    
}

}