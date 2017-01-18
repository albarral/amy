/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdexcept>      // std::invalid_argument

#include "amy/test/Interpreter.h"

namespace amy
{
// Constructor 
Interpreter::Interpreter()
{    
    // text initially expected
    bcomplete = false;   
    mode = eMODE_TEXTUAL;    
    action = eACT_INVALID;

    // arm input commands
    movePan = "pan";
    moveTilt = "tilt";
    moveRadius ="radius";
    armStop = "sto";
    // joint input commands
    moveHS = "hs";
    moveVS = "vs";
    moveELB = "elb";
    moveHWRI = "hwri";
    moveVWRI= "vwri";
    // amy process input commands
    amyEnd = "end";
 }



void Interpreter::checkCommand(std::string input)
{
    // if numeric mode
    if (mode == eMODE_NUMERIC)
    {
        int x;
        // if numeric, command is complete
        if (isNumeric(input, x))
        {
            value = (float)x;
            bcomplete = true;            
        }
        // if not numeric, toggle mode
        else
        {
            toggleMode();
            bcomplete = false;
        }        
    }
    
    // if textual mode, check command and toggle mode
    if (mode == eMODE_TEXTUAL)
    {
        bool bfound = checkArmCommand(input);
        
        if (!bfound)
            bfound = checkJointCommand(input);    

        if (!bfound)
            bfound = checkAmyCommand(input);    

        toggleMode();
        
        // if command not found, invalid
        if (!bfound)
        {
            action = eACT_INVALID;
            bcomplete = true;            
        }                        
    }
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

bool Interpreter::checkArmCommand(std::string input)
{
    bool bfound = false;

     if (input.compare(movePan) == 0) 
    {
        action = eACT_MOVE_PAN;
        bfound = true;
    }
    else if (input.compare(moveTilt) == 0) 
    {
        action = eACT_MOVE_TILT;
        bfound = true;
    } 
    else if (input.compare(moveRadius) == 0) 
    {
        action = eACT_MOVE_RADIUS;        
        bfound = true;
    } 

    if (bfound)
        bcomplete = false;
    
    return bfound;
}


bool Interpreter::checkJointCommand(std::string input)
{
    bool bfound = false;

     if (input.compare(moveHS) == 0) 
    {
        action = eACT_POS_HS;
        bfound = true;
    }
    else if (input.compare(moveVS) == 0) 
    {
        action = eACT_POS_VS;
        bfound = true;
    } 
    else if (input.compare(moveELB) == 0) 
    {
        action = eACT_POS_ELB;        
        bfound = true;
    } 
    else if (input.compare(moveHWRI) == 0) 
    {
        action = eACT_POS_HWRI;        
        bfound = true;
    } 
    else if (input.compare(moveVWRI) == 0) 
    {
        action = eACT_POS_VWRI;        
        bfound = true;
    } 

    if (bfound)
        bcomplete = false;
    
    return bfound;
}

bool Interpreter::checkAmyCommand(std::string input)
{
    bool bfound = false;

     if (input.compare(amyEnd) == 0) 
    {
        action = eACT_AMY_END;
        bfound = true;
        // this command needs no value, it's complete
        bcomplete = true;
    }
    
    return bfound;
}

void Interpreter::toggleMode()
{
    if (mode == eMODE_TEXTUAL)
        mode = eMODE_NUMERIC;
    else
        mode = eMODE_TEXTUAL;
}
    
std::vector<std::string> Interpreter::getArmCommands()
{
    std::vector<std::string> list;
    
    list.push_back(movePan);
    list.push_back(moveTilt);
    list.push_back(moveRadius);
    list.push_back(armStop);
    
    return list;
}

std::vector<std::string> Interpreter::getJointCommands()
{
    std::vector<std::string> list;
    
    list.push_back(moveHS);
    list.push_back(moveVS);
    list.push_back(moveELB);
    list.push_back(moveHWRI);
    list.push_back(moveVWRI);
    
    return list;
}

std::vector<std::string> Interpreter::getAmyCommands()
{
    std::vector<std::string> list;
    
    list.push_back(amyEnd);
    
    return list;
}

}