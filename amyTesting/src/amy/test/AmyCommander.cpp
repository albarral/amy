/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream>
#include "log4cxx/ndc.h"

#include "amy/test/AmyCommander.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AmyCommander::logger(Logger::getLogger("amy.test"));

// Constructor 
AmyCommander::AmyCommander()
{    
    modName = "ConsoleCommander";
    entry = "";
 }

void AmyCommander::init()
{
    // nothing done    
    LOG4CXX_INFO(logger, modName << " initialized");      
};

void AmyCommander::first()
{    
    log4cxx::NDC::push(modName);   	
    showCommandsList();
}

void AmyCommander::loop()
{
    // listen to user commands
    if (listen())
    {
        if (entry.compare("quit") == 0)
        {
            Module2::off();
            return;
        }
        
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


bool AmyCommander::listen()
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
void AmyCommander::sendCommand(int action, float value)
{
    switch (action)
    {
        case Interpreter::eACT_MOVE_PAN:            
            //oAmyFileClient.movePan(value);
            oAmyZeroMQClient.movePan(value);
            break;

        case Interpreter::eACT_MOVE_TILT:
            //oAmyFileClient.moveTilt(value);
            oAmyZeroMQClient.moveTilt(value);
            break;

        case Interpreter::eACT_MOVE_RADIUS:
            //oAmyFileClient.moveRadius(value);
            oAmyZeroMQClient.moveRadius(value);
            break;

        case Interpreter::eACT_POS_HS:
            //oAmyFileClient.setPosHS(value);
            oAmyZeroMQClient.setPosHS(value);
            break;

        case Interpreter::eACT_POS_VS:
            //oAmyFileClient.setPosVS(value);
            oAmyZeroMQClient.setPosVS(value);
            break;

        case Interpreter::eACT_POS_ELB:
            //oAmyFileClient.setPosELB(value);
            oAmyZeroMQClient.setPosELB(value);
            break;

        case Interpreter::eACT_POS_HWRI:
            //oAmyFileClient.setPosHW(value);
            oAmyZeroMQClient.setPosHW(value);
            break;

        case Interpreter::eACT_POS_VWRI:
            //oAmyFileClient.setPosVW(value);
            oAmyZeroMQClient.setPosVW(value);
            break;

        case Interpreter::eACT_AMY_END:
            //oAmyFileClient.endAmy();
            oAmyZeroMQClient.endAmy();
            break;
            
        default:
            LOG4CXX_ERROR(logger, "client request not available!");                  
            break;
    }
}


void AmyCommander::showCommandsList()
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