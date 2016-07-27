/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream>
#include <stdexcept>      // std::invalid_argument
#include "log4cxx/ndc.h"

#include "amy/arm/coms/ArmComs1.h"
#include "amy/arm/coms/ArmCommand.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmComs1::logger(Logger::getLogger("amy.arm"));

// Constructor 
ArmComs1::ArmComs1 ()
{    
    benabled = false;

    commandType = eCOM_EMPTY;    
    targetJoint = -1;   // default invalid value
    comsJSelection = "j";
    comsJForward = "for";
    comsJBackward = "bac";
    comsJKeep = "kip";
    comsJBrake = "bra";
    comsJStop = "sto";
    comsArmMovement = "mov";
    comsEnd = "end";
 }

// Destructor
ArmComs1::~ArmComs1 ()
{
    listCommands.clear();
}

void ArmComs1::init ()
{
    // list of normal movement commands
    listCommands = {comsJForward, 
                               comsJBackward,
                               comsJKeep,
                               comsJBrake,
                               comsJStop,                               
                               comsEnd};

    // list of extended movement commands
    listExtendedCommands = {comsArmMovement};

    listDescriptions = {"move joint forward",
                                "move joint backwards",
                                "keep joint speed",
                                "brake joint",
                                "stop joint",
                                "stop arm control"};

    listExtendedDescriptions = {"start/stop predefined movement"};
    
    benabled = true;    
    LOG4CXX_INFO(logger, "ArmComs1 initialized");          
};

void ArmComs1::connect(ArmBus& oBus)
{
    pBus = &oBus;
    oArmCommander.connect(oBus);
    bconnected = true;

    LOG4CXX_DEBUG(logger, "ArmComs1 connected to bus");      
}

void ArmComs1::first()
{    
    log4cxx::NDC::push("ArmComs1");   	
    showCommandsList();
}

void ArmComs1::loop()
{
    bool bret = false;
    LOG4CXX_INFO(logger, "> ?");    

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
    else if (commandType == eCOM_SELECTION)
    {
        targetJoint = extractNumericSuffix(entry);       
        LOG4CXX_INFO(logger, "Selected joint: " << targetJoint);  
    }
    else if (commandType == eCOM_MOVEMENT)
    {
        bret = buildMovementCommand();
        if (bret)
            sendCommand();            
    }
    else if (commandType == eCOM_POSITION)
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
    
    // set as default
    commandType = eCOM_INVALID;
    
    // analyze user's entry
    if (!entry.empty())
    {        
        switch (entry.length())
        {
            case lenSelection:                
                // check if it's a selection command 
                if (checkSelectionCommand())
                    commandType = eCOM_SELECTION;
                break;
                
            case lenCommand:
                // check if it's a movement command 
                if (checkMovementCommand())
                    commandType = eCOM_MOVEMENT;
                // check if it's a position command 
                else if (checkNumericValue(entry))                    
                    commandType = eCOM_POSITION;
                break;
                
            case lenExtended:
                // check if it's an extended movement command 
                if (checkExtendedCommand())
                    commandType = eCOM_MOVEMENT;
                break;
        }
    }    
    // empty command
    else        
        commandType = eCOM_EMPTY;
}


// checks if entered command is a joint selection one
bool ArmComs1::checkSelectionCommand()
{
    // get first letter of the entered command
    std::string base = entry.substr(0, 1);
    // compare it with the selection command
    if (base.compare(comsJSelection) == 0) 
        return true;
    else
        return false;
}


// checks if entered command is a normal movement one 
bool ArmComs1::checkMovementCommand()
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


// checks if entered command is an extended movement one     
bool ArmComs1::checkExtendedCommand()
{
    bool bfound = false;
                
    // search the entered command in the list of commands
    for (std::string& command : listExtendedCommands)
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
    std::string base = "";

    oArmCommand.resetCommand();
    
    // extract base in case of extended command 
    if (entry.length() == lenExtended)            
        base = entry.substr(0, lenCommand);
    else
        base = entry;
        
    // joint forward 
    if (base.compare(comsJForward) == 0) 
    {
        targetAction = ArmCommand::eACT_JOINT_FORWARD;
    }
    // joint backwards
    else if (base.compare(comsJBackward) == 0) 
    {
        targetAction = ArmCommand::eACT_JOINT_BACKWARDS;
    } 
    // joint keep speed
    else if (base.compare(comsJKeep) == 0) 
    {
        targetAction = ArmCommand::eACT_JOINT_KEEP;        
    } 
    // joint brake
    else if (base.compare(comsJBrake) == 0) 
    {
        targetAction = ArmCommand::eACT_JOINT_BRAKE;
    } 
    // joint stop
    else if (base.compare(comsJStop) == 0) 
    {
        targetAction = ArmCommand::eACT_JOINT_STOP;
    } 
    // predefined arm movement
    else if (base.compare(comsArmMovement) == 0) 
    {
        // obtain action number
        int action = extractNumericSuffix(entry);  

        // start move
        if (action == 1)
            targetAction = ArmCommand::eACT_MOVEMENT_START;
        // stop move
        else if (action == 2)
            targetAction = ArmCommand::eACT_MOVEMENT_STOP;
    } 
    // end arm control
    else if (base.compare(comsEnd) == 0) 
    {            
        targetAction = ArmCommand::eACT_ARM_END;
    } 
    
    // set target action
    if (targetAction != ArmCommand::eACT_UNDEFINED)
        bret = oArmCommand.setTargetAction(targetAction);        
            
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

    int targetAction = ArmCommand::eACT_JOINT_SET;

    // set target action
    bret = oArmCommand.setTargetAction(targetAction);        
            
    // set target joint
    if (bret)
        bret = oArmCommand.setTargetJoint(targetJoint);        
    
    // set target value
    if (bret)        
        bret = oArmCommand.setTargetValue(value);

    // build command
    if (bret)
        bret = oArmCommand.buildBusCommand();

    return bret;
}

// send command through the bus
void ArmComs1::sendCommand()
{
    if (oArmCommander.sendCommand(oArmCommand))
    {
        LOG4CXX_INFO(logger, "command sent");      
    }
    else
    {
        LOG4CXX_INFO(logger, "command not sent");             
    }
}

// extract numeric suffix (last character) of a string
int ArmComs1::extractNumericSuffix(std::string input)
{
    int number;
    try
    {
        // extract suffix
        int len = entry.length();        
        std::string suffix = entry.substr(len-1, 1);          
        number = std::stoi(suffix);        
    }
    catch (std::invalid_argument) 
    {
        number = -1;     // invalid numeric suffix
    }
    return number;
}


void ArmComs1::showCommandsList()
{    
    LOG4CXX_INFO(logger, "Usage: control the arm by alternating joint selection commands with movement commands or position commands ...");      

    std::vector<std::string>::iterator it_command, it_description, it_extcommand, it_extdescription;
    it_command = listCommands.begin();
    it_description = listDescriptions.begin();
    it_extcommand = listExtendedCommands.begin();
    it_extdescription = listExtendedDescriptions.begin();

    LOG4CXX_INFO(logger, "Joint selection commands:");      

    LOG4CXX_INFO(logger, comsJSelection << "1 -> use joint 1 (horizontal shoulder)");             
    LOG4CXX_INFO(logger, comsJSelection << "2 -> use joint 2 (vertical shoulder)");             
    LOG4CXX_INFO(logger, comsJSelection << "3 -> use joint 3 (elbow)");             
    LOG4CXX_INFO(logger, comsJSelection << "4 -> use joint 4 (vertical wrist)");             

    LOG4CXX_INFO(logger, "Simple movement commands:");      

    while (it_command != listCommands.end())
    {
        LOG4CXX_INFO(logger, *it_command << " -> " << *it_description);             
        it_command++;
        it_description++;
    }
    
    LOG4CXX_INFO(logger, "Extended movement commands:");      

    while (it_extcommand != listExtendedCommands.end())
    {
        LOG4CXX_INFO(logger, *it_extcommand << " -> " << *it_extdescription);             
        it_extcommand++;
        it_extdescription++;
    }

    LOG4CXX_INFO(logger, "Joint position commands:");      

    LOG4CXX_INFO(logger, "120 -> move joint to angle 120");             
}

}