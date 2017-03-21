/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/console/AmyConnector.h"
#include "amy/console/Interpreter.h"
#include "amy/coms/file/AmyFileClient.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AmyConnector::logger(Logger::getLogger("amy.console"));

// Constructor 
AmyConnector::AmyConnector()
{    
    pAmyClient = 0;
 }

AmyConnector::~AmyConnector()
{
    if (pAmyClient != 0)
        delete (pAmyClient);
}

void AmyConnector::connect2Amy()
{
    pAmyClient = new AmyFileClient();     // amy file client   
};

// send command through the bus
bool AmyConnector::sendCommand(int action, float value)
{
    if (pAmyClient == 0)
    {
        LOG4CXX_ERROR(logger, "AmyConnector: not connected to amy");                        
        return false;
    }
    
    bool bsent = true;
    switch (action)
    {
        // axis speeds
        case Interpreter::eCMD_PAN_SPEED:
            pAmyClient->getAxisClient().panSpeed(value);
            pAmyClient->sendAxisCommand();
            break;
        case Interpreter::eCMD_TILT_SPEED:
            pAmyClient->getAxisClient().tiltSpeed(value);
            pAmyClient->sendAxisCommand();
            break;
        case Interpreter::eCMD_RADIAL_SPEED:
            pAmyClient->getAxisClient().radialSpeed(value);
            pAmyClient->sendAxisCommand();
            break;
        
        // axis positions
        case Interpreter::eCMD_PAN_POS:            
            pAmyClient->getAxisClient().movePan(value);
            pAmyClient->sendAxisCommand();
            break;
        case Interpreter::eCMD_TILT_POS:
            pAmyClient->getAxisClient().moveTilt(value);
            pAmyClient->sendAxisCommand();
            break;
        case Interpreter::eCMD_RADIUS_POS:
            pAmyClient->getAxisClient().moveRadius(value);
            pAmyClient->sendAxisCommand();
            break;
            
        // joint positions
        case Interpreter::eCMD_MOVE_HS:
            pAmyClient->getJointClient().setPosHS(value);
            pAmyClient->sendJointCommand();
            break;
        case Interpreter::eCMD_MOVE_VS:
            pAmyClient->getJointClient().setPosVS(value);
            pAmyClient->sendJointCommand();
            break;
        case Interpreter::eCMD_MOVE_ELB:
            pAmyClient->getJointClient().setPosELB(value);
            pAmyClient->sendJointCommand();
            break;
        case Interpreter::eCMD_MOVE_HWRI:
            pAmyClient->getJointClient().setPosHW(value);
            pAmyClient->sendJointCommand();
            break;
        case Interpreter::eCMD_MOVE_VWRI:
            pAmyClient->getJointClient().setPosVW(value);
            pAmyClient->sendJointCommand();
            break;

         // arm commands
        case Interpreter::eCMD_KEEP_TILT:
            pAmyClient->getOtherClient().keepTilt(1);
            pAmyClient->sendOtherCommand();
            break;
        case Interpreter::eCMD_AMY_END:
            pAmyClient->getOtherClient().endAmy();
            pAmyClient->sendOtherCommand();
            break;
        case Interpreter::eCMD_ARM_STOP:
            pAmyClient->toDoCommand();
            break;
            
        default:
            LOG4CXX_ERROR(logger, "AmyConnector: client request not available!");        
            bsent = false;
            break;
    }
    return bsent;
}

}