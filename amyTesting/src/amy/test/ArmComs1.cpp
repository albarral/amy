/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream>
#include <stdexcept>      // std::invalid_argument
#include "log4cxx/ndc.h"

#include "amy/test/ArmComs1.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmComs1::logger(Logger::getLogger("amy.test"));

// Constructor 
ArmComs1::ArmComs1()
{    
    modName = "ArmComs1";
    bExpectingNumber = false;   // text is initially expected
    
    commandType = eCOM_EMPTY;    
    targetJoint = -1;   // default invalid value
    comsPan = "pan";
    comsTilt = "til";
    comsExtend ="ext";
    horizontal_shoulder = "hs";
    vertical_shoulder = "vs";
    elbow = "el";
    horizontal_wrist = "hw";
    vertical_wrist = "vw";
    comsJStop = "sto";
    comsMovement = "mov";
    comsEnd = "end";
 }

// Destructor
ArmComs1::~ArmComs1 ()
{
    listCommands.clear();
}

void ArmComs1::init()
{
    // list of normal movement commands
    listCommands = {
        horizontal_shoulder,
        vertical_shoulder, 
        elbow, 
        horizontal_wrist,
        vertical_wrist,
        comsPan,
        comsTilt,
        comsExtend,
        comsJStop,                         
        comsMovement,
        comsEnd};

    listDescriptions = {
        "select horizontal_shoulder",
        "select vertical_shoulder", 
        "select elbow", 
        "select horizontal_wrist",
        "select vertical_wrist",
        "change pan",
        "change tilt",
        "change extension",
        "stop joint",        
        "do predefined movement",
        "stop arm control"};
    
    benabled = true;    
    LOG4CXX_INFO(logger, modName << " initialized");      
};

void ArmComs1::first()
{    
    log4cxx::NDC::push(modName);   	
    showCommandsList();
}

void ArmComs1::loop()
{
    bool bret = false;
    LOG4CXX_INFO(logger, "> ?");    

    // reset armed flag
    bArmedCommand = false;
    
    // listen to user commands
    listen();

    // process and send command
    if (commandType == eCOM_EMPTY)
    {
        LOG4CXX_ERROR(logger, "Empty command!");
    }
    else if (commandType == eCOM_INVALID)
    {
        LOG4CXX_ERROR(logger, "Invalid command! - " << entry);            
    }
    else if (commandType == eCOM_UNKNOWN)
    {
        LOG4CXX_ERROR(logger, "Unknown command! - " << entry);            
    }
    else if (commandType == eCOM_MOVEMENT && bArmedCommand)
    {
        bret = buildMovementCommand();
        if (bret)
            sendCommand();            
    }
    else if (commandType == eCOM_POSITION && bArmedCommand)
    {
        bret = buildPositionCommand();
        if (bret)
            sendCommand();            
    }        
}


void ArmComs1::listen()
{
    // get input from console
    std::getline(std::cin, entry);    
    // show input
    LOG4CXX_INFO(logger, "< " << entry);
       
    // analyze user's entry
    if (!entry.empty())
    {
        // numeric input
        if (checkNumericValue(entry))
        {
            // if number expected, command armed 
            if (bExpectingNumber)
                bArmedCommand = true;
            // if text expected, invalid
            else
                commandType = eCOM_INVALID;                
        }
        // text input, analyze it
        else
            analyseText();
    }    
    // empty command
    else        
        commandType = eCOM_EMPTY;
}

void ArmComs1::analyseText()
{
    // initially unknown
    commandType = eCOM_UNKNOWN;
    switch (entry.length())
    {
        case lenSelection:                
            // if selection command, expect numeric positions
            if (checkValidCommand())
            {
                commandType = eCOM_POSITION;
                targetJoint = entry;
                bExpectingNumber = true;                
            }
            break;

        case lenCommand:
            // check if it's a movement command 
            if (checkValidCommand())
            {
                commandType = eCOM_MOVEMENT;
                base = entry;
                // if complex command, expect numeric value
                if (checkNeedsCompletion())
                    bExpectingNumber = true;                
                // otherwise, send it now
                else
                {
                    bExpectingNumber = false;                
                    bArmedCommand = true;
                }                    
            }
            break;
    }    
}


// checks if entered command is a valid one 
bool ArmComs1::checkValidCommand()
{
    bool bfound = false;
                
    // search the entered command in the list of commands
    for (std::string& command : listCommands)
    {
        // if found finish search
        if (entry.compare(command) == 0) 
        {
            bfound = true;                    
            break;
        }
    }
         
    return bfound;
}

// checks if entered command is a joint selection one
bool ArmComs1::checkNeedsCompletion()
{
    if (entry.compare(comsEnd) == 0)
        return false;
    else 
        return true;;
}

// checks if the specified text is a number
bool ArmComs1::checkNumericValue(std::string input)
{
    try
    {
        // try converting string to integer
        value = std::stoi(input);
        return true;
    }
    catch (std::invalid_argument) 
    {
        // if conversion fails it's not a number
        return false;        
    }
}

// builds a suitable control command to be sent through the bus
bool ArmComs1::buildMovementCommand()
{
    int targetAction = ArmCommand::eACT_UNDEFINED;
    bool bret = false;

    oArmCommand.resetCommand();
            
    if (base.compare(comsPan) == 0) 
    {
        targetAction = ArmCommand::eACT_SET_PAN;
    }
    else if (base.compare(comsTilt) == 0) 
    {
        targetAction = ArmCommand::eACT_SET_TILT;
    } 
    else if (base.compare(comsExtend) == 0) 
    {
        targetAction = ArmCommand::eACT_SET_EXTENSION;        
    } 
    // joint stop
    else if (base.compare(comsJStop) == 0) 
    {
        targetAction = ArmCommand::eACT_JOINT_STOP;
    } 
    // predefined movement
    else if (base.compare(comsMovement) == 0) 
    {
        // obtain action number
        int action = value;

        // start move
        if (action == 1)
            targetAction = ArmCommand::eACT_MOVEMENT_START;
        // stop move
        else if (action == 0)
            targetAction = ArmCommand::eACT_MOVEMENT_STOP;
    } 
    // end arm control
    else if (base.compare(comsEnd) == 0) 
    {            
        targetAction = ArmCommand::eACT_ARM_END;
    } 
    
    // set target action
    if (targetAction != ArmCommand::eACT_UNDEFINED)
    {
        bret = oArmCommand.setTargetAction(targetAction);        
        oArmCommand.setTargetValue(value);
    }
            
    // set target joint
    if (bret && ArmCommand::isJointAction(targetAction))
        oArmCommand.setTargetJoint(targetJoint);        
    
    // build command
    if (bret)
        bret = oArmCommand.buildBusCommand();

    return bret;
}

// builds joint position control commands to be sent through the bus
bool ArmComs1::buildPositionCommand()
{    
    bool bret = false;

    int targetAction = ArmCommand::eACT_JOINT_ANGLE;

    // set target action
    bret = oArmCommand.setTargetAction(targetAction);        
            
    // build arm command
    if (bret)
    {
        oArmCommand.setTargetJoint(targetJoint);        
        oArmCommand.setTargetValue(value);
        bret = oArmCommand.buildBusCommand();
    }

    return bret;
}

// send command through the bus
void ArmComs1::sendCommand()
{
    if (oArmCommander.sendCommand(pArmBus, oArmCommand))
    {
        LOG4CXX_INFO(logger, "command sent");      
        //LOG4CXX_INFO(logger, pBus->toString());
    }
    else
    {
        LOG4CXX_INFO(logger, "command not sent");             
    }
}


void ArmComs1::showCommandsList()
{    
    LOG4CXX_INFO(logger, "Control the arm by using next commands (most need completion with a numeric value)");      

    std::vector<std::string>::iterator it_command, it_description;
    it_command = listCommands.begin();
    it_description = listDescriptions.begin();

    LOG4CXX_INFO(logger, "Accepted commands:");      

    while (it_command != listCommands.end())
    {
        LOG4CXX_INFO(logger, *it_command << " -> " << *it_description);             
        it_command++;
        it_description++;
    }    
}

}