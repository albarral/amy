/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdexcept>      // std::invalid_argument

#include "amy/console/Interpreter.h"

namespace amy
{
// Constructor 
Interpreter::Interpreter()
{    
    state = eSTATE_CHECK_FIRST;

    buildListCommands();
}

void Interpreter::buildListCommands()
{
    // define user commands
    UserCommand oCommands[14];         
    // joint positions 
    oCommands[0] = UserCommand("hs", eCMD_MOVE_HS, UserCommand::eCOM_COMPLEX, "move horizontal shoulder joint (degrees)");
    oCommands[1] = UserCommand("vs", eCMD_MOVE_VS, UserCommand::eCOM_COMPLEX, "move vertical shoulder joint (degrees)");
    oCommands[2] = UserCommand("elb", eCMD_MOVE_ELB, UserCommand::eCOM_COMPLEX, "move elbow joint (degrees)");
    oCommands[3] = UserCommand("hwri", eCMD_MOVE_HWRI, UserCommand::eCOM_COMPLEX, "move horizontal wrist joint (degrees)");
    oCommands[4] = UserCommand("vwri", eCMD_MOVE_VWRI, UserCommand::eCOM_COMPLEX, "move vertical wrist joint (degrees)");
    // axis positions 
    oCommands[5] = UserCommand("pan", eCMD_PAN_POS, UserCommand::eCOM_COMPLEX, "move pan (degrees)");
    oCommands[6] = UserCommand("tilt", eCMD_TILT_POS, UserCommand::eCOM_COMPLEX, "move tilt (degrees)");
    oCommands[7] = UserCommand("rad", eCMD_RADIUS_POS, UserCommand::eCOM_COMPLEX, "move radius (cm)");
    oCommands[8] = UserCommand("keep", eCMD_KEEP_TILT, UserCommand::eCOM_COMPLEX, "keep tilt position (1 or 0)");
    // axis speeds
    oCommands[9] = UserCommand("vpan", eCMD_PAN_SPEED, UserCommand::eCOM_COMPLEX, "move pan at given speed (degrees/s)");
    oCommands[10] = UserCommand("vtilt", eCMD_TILT_SPEED, UserCommand::eCOM_COMPLEX, "move tilt at given speed (degrees/s)");
    oCommands[11] = UserCommand("vrad", eCMD_RADIAL_SPEED, UserCommand::eCOM_COMPLEX, "move radius at given speed (cm/s)");
    // arm commands
    oCommands[12] = UserCommand("stop", eCMD_ARM_STOP, UserCommand::eCOM_SIMPLE, "stop arm");
    oCommands[13] = UserCommand("end", eCMD_AMY_END, UserCommand::eCOM_SIMPLE, "end amy");
    
    // insert them in list
    listCommands.clear();
    for (int i=0; i<14; i++)
    {
        listCommands.push_back(oCommands[i]);
    }
}


void Interpreter::checkCommand(std::string entry1, std::string entry2)
{  
    // not valid till correctly checked
    state = eSTATE_CHECK_FIRST;
    // search command in commands list
    for (UserCommand& oCommand : listCommands)
    {
        // if found, take note and skip search
        if (entry1.compare(oCommand.getName()) == 0)
        {
            action = oCommand.getCode();
            // if simple command -> valid
            if (oCommand.isSimple())
                state = eSTATE_OK_VALID;
            // if complex command -> check second part
            else
                state = eSTATE_CHECK_SECOND;
            break;
        }        
    }

    // if not found -> unknown
    if (state == eSTATE_CHECK_FIRST)
        state = eSTATE_KO_UNKNOWN;
        
    // nothing more to check, skip
    if (state != eSTATE_CHECK_SECOND)
        return;

    // It's a complex command. Let's check the second part  ...

    // if no second part -> incomplete
    if (entry2.empty())
    {
        state = eSTATE_KO_INCOMPLETE;
        return;            
    }

    // if second part is numeric value -> valid
    int x;
    if (isNumeric(entry2, x))
    {
        value = (float)x;
        state = eSTATE_OK_VALID;        
    }
    // otherwise -> invalid
    else
        state = eSTATE_KO_INVALID;

}

// checks if the specified text is a number
bool Interpreter::isNumeric(std::string input, int& val)
{
    try
    {
        // try converting string to integer
        val = std::stoi(input);
        return true;
    }
    catch (std::invalid_argument) 
    {
        // if conversion fails it's not a number
        return false;        
    }
}

std::string Interpreter::getResult()
{
    std::string result;
    switch (state)
    {
        case eSTATE_KO_UNKNOWN:
            result = "unknown command";
            break;
        case eSTATE_KO_INCOMPLETE:
            result = "incomplete command";
            break;
        case eSTATE_KO_INVALID:
            result = "invalid value";
            break;
        case eSTATE_OK_VALID:
            result = "ok";
            break;            
    }    
    return result;
}

std::string Interpreter::getAvailableCommands()
{
    std::string text ="";
    
    for (UserCommand& oCommand : listCommands)
    {
        text += "\t" + oCommand.getName() + "\t" + oCommand.getDescription() + "\n";
    }
    return text;
}

}