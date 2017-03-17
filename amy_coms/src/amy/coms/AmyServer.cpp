/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/coms/AmyServer.h"

namespace amy
{
log4cxx::LoggerPtr AmyServer::logger(log4cxx::Logger::getLogger("amy.server"));

AmyServer::AmyServer()
{    
    bconnected = false;
    pArmInterface = 0;
    bamyEndRequested = false;
}

void AmyServer::connect2Arm(iArmInterface& oArmInterface)
{
    pArmInterface = &oArmInterface;
    bconnected = true;
}

// CYCLIC MOVEMENTS
void AmyServer::panFrequency(float value)
{
    if (bconnected)
        pArmInterface->panFrequency(value);
}
// set pan amplitude (degrees)
void AmyServer::panAmplitude(float value)
{
    if (bconnected)
        pArmInterface->panAmplitude(value);
}
// trigger pan cyclic movement
void AmyServer::panTrigger()
{
    if (bconnected)
        pArmInterface->panTrigger();
}
// stop pan cyclic movement
void AmyServer::panStop()
{
    if (bconnected)
        pArmInterface->panStop();
}

// AXIS SPEEDS
void AmyServer::panSpeed(float value)
{
    if (bconnected)
        pArmInterface->panSpeed(value);
}
void AmyServer::tiltSpeed(float value)
{
    if (bconnected)
        pArmInterface->tiltSpeed(value);
}
void AmyServer::radialSpeed(float value)
{
    if (bconnected)
        pArmInterface->radialSpeed(value);
}
void AmyServer::keepTilt(int value)
{
    if (bconnected)
        pArmInterface->keepTilt(value);
}

    // AXIS POSITIONS    
void AmyServer::movePan(float value)
{    
    if (bconnected)
        pArmInterface->movePan(value);
}
void AmyServer::moveTilt(float value)
{
    if (bconnected)
        pArmInterface->moveTilt(value);
}
void AmyServer::moveRadius(float value)
{
    if (bconnected)
        pArmInterface->extend(value);
}

    // JOINT POSITIONS
void AmyServer::setPosHS(float value)
{
    if (bconnected)
        pArmInterface->moveHS(value);    
}
void AmyServer::setPosVS(float value)
{
    if (bconnected)
        pArmInterface->moveVS(value);    
}
void AmyServer::setPosELB(float value)
{
    if (bconnected)
        pArmInterface->moveEL(value);    
}
void AmyServer::setPosHW(float value)
{
    if (bconnected)
        pArmInterface->moveHW(value);    
}
void AmyServer::setPosVW(float value)
{
    if (bconnected)
        pArmInterface->moveVW(value);    
}

// AMY COMMANDS
void AmyServer::endAmy()
{
    bamyEndRequested = true;    
}

void AmyServer::toDoCommand(float value)
{
    // nothing done
    // dummy method for to do commands
    LOG4CXX_INFO(logger, "> to do");                        
}
 
bool AmyServer::checkCommand(std::string text)
{              
    bvalid = oAmyCommand.interpret(text);
    LOG4CXX_DEBUG(logger, "AmyServer: command = " << oAmyCommand.getDescription()); 
    return bvalid;
}
    
bool AmyServer::processCommand()
{
    bool bret;
    switch (oAmyCommand.getCategory())
    {
        case AmyCommand::eCAT_JOINT_CMD:
            bret = processJointCommand();
            break;
            
        case AmyCommand::eCAT_AXIS_CMD:
            bret = processAxisCommand();
            break;

        case AmyCommand::eCAT_ARM_CMD:
            bret = processArmCommand();
            break;

        case AmyCommand::eCAT_AMY_CMD:
            bret = processAmyCommand();
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "AmyServer: unknown command " << oAmyCommand.getDescription());                        
    }    
    return bret;
}

bool AmyServer::processJointCommand()
{
    bool bret = true;
    float value = oAmyCommand.getValue();

    switch (oAmyCommand.getAction())
    {
        case AmyCommand::eJOINT_HS_POS:
            LOG4CXX_INFO(logger, "> set HS " << value);                        
            setPosHS(value);
            break;
            
        case AmyCommand::eJOINT_VS_POS:
            LOG4CXX_INFO(logger, "> set VS " << value);                        
            setPosVS(value);
            break;

        case AmyCommand::eJOINT_ELB_POS:
            LOG4CXX_INFO(logger, "> set ELB " << value);                        
            setPosELB(value);
            break;

        case AmyCommand::eJOINT_HWRI_POS:
            LOG4CXX_INFO(logger, "> set HW " << value);                        
            setPosHW(value);
            break;

        case AmyCommand::eJOINT_VWRI_POS:
            LOG4CXX_INFO(logger, "> set VW " << value);                        
            setPosVW(value);
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "AmyServer: unknown command " << oAmyCommand.getDescription());           
    }    
    return bret;
}

bool AmyServer::processAxisCommand()
{
    bool bret = true;
    float value = oAmyCommand.getValue();
    
    switch (oAmyCommand.getAction())
    {
        case AmyCommand::eAXIS_PAN_POS:
            LOG4CXX_INFO(logger, "> move pan " << value);                        
            movePan(value);
            break;
            
        case AmyCommand::eAXIS_TILT_POS:
            LOG4CXX_INFO(logger, "> move tilt " << value);                        
            moveTilt(value);
            break;

        case AmyCommand::eAXIS_RAD_POS:
            LOG4CXX_INFO(logger, "> move radius " << value);                        
            moveRadius(value);
            break;

        case AmyCommand::eAXIS_PAN_SPEED:
            LOG4CXX_INFO(logger, "> pan speed " << value);                        
            panSpeed(value);
            break;
            
        case AmyCommand::eAXIS_TILT_SPEED:
            LOG4CXX_INFO(logger, "> tilt speed " << value);                        
            tiltSpeed(value);
            break;

        case AmyCommand::eAXIS_RAD_SPEED:
            LOG4CXX_INFO(logger, "> rad speed " << value);                        
            radialSpeed(value);
            break;
            
        default:
            bret = false;
            LOG4CXX_WARN(logger, "AmyServer: unknown command " << oAmyCommand.getDescription());           
    }    
    return bret;
}


bool AmyServer::processArmCommand()
{
    bool bret = true;
    float value = oAmyCommand.getValue();
    
    switch (oAmyCommand.getAction())
    {
        case AmyCommand::eARM_STOP:
            LOG4CXX_INFO(logger, "> arm stop ");                        
            toDoCommand(value);
            break;
            
        case AmyCommand::eARM_KEEP_TILT:
            LOG4CXX_INFO(logger, "> keep tilt " << value);                        
            keepTilt((int)value);
            break;
            
        default:
            bret = false;
            LOG4CXX_WARN(logger, "AmyServer: unknown command " << oAmyCommand.getDescription());           
    }    
    return bret;
}

bool AmyServer::processAmyCommand()
{
    bool bret = true;
    float value = oAmyCommand.getValue();
    
    switch (oAmyCommand.getAction())
    {
        case AmyCommand::eAMY_END:
            LOG4CXX_INFO(logger, "> end emy");                        
            endAmy();
            break;
            
        default:
            bret = false;
            LOG4CXX_WARN(logger, "AmyServer: unknown command " << oAmyCommand.getDescription());           
    }    
    return bret;
}
}