/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/console/AmyConnector.h"
#include "amy/console/Interpreter.h"
#include "amy/coms/file/AmyFileClient.h"
#include "amy/coms/zero/AmyZeroMQClient.h"
#include "amy/coms/dictionary/ComsCategory.h"
#include "amy/coms/dictionary/JointCategory.h"
#include "amy/coms/dictionary/AxisCategory.h"
#include "amy/coms/dictionary/CyclicCategory.h"
#include "amy/coms/dictionary/OtherCategory.h"
#include "amy/coms/sections/JointClient.h"
#include "amy/coms/sections/AxisClient.h"
#include "amy/coms/sections/CyclicClient.h"
#include "amy/coms/sections/OtherClient.h"

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
    //pAmyClient = new AmyFileClient();     // amy file client 
    pAmyClient= new AmyZeroMQClient();     // amy zero client
    pAmyClient->setPort(5555);
};

// send command through the bus
bool AmyConnector::sendCommand(int category, int action, float value)
{
    if (pAmyClient == 0)
    {
        LOG4CXX_ERROR(logger, "AmyConnector: not connected to amy");                        
        return false;
    }
    
    bool bsent = true;
    switch (category)
    {
        case ComsCategory::eCATEGORY_JOINTS:
            bsent = sendJointCommand(action, value);
            break;
        case ComsCategory::eCATEGORY_AXIS:
            bsent = sendAxisCommand(action, value);
            break;
        case ComsCategory::eCATEGORY_CYCLIC:
            bsent = sendCyclicCommand(action, value);
            break;
        case ComsCategory::eCATEGORY_OTHER:
            bsent = sendOtherCommand(action, value);
            break;
            
        default:
            LOG4CXX_ERROR(logger, "AmyConnector: coms category not available!");        
            bsent = false;
            break;
    }
    return bsent;
}

bool AmyConnector::sendJointCommand(int action, float value)
{    
    bool bsent = true;
    
    JointClient& oJointClient = pAmyClient->getJointClient();
    switch (action)
    {
        // joint positions
        case JointCategory::eJOINT_HS_POS:
            oJointClient.setPosHS(value);
            pAmyClient->sendJointCommand();
            break;
        case JointCategory::eJOINT_VS_POS:
            oJointClient.setPosVS(value);
            pAmyClient->sendJointCommand();
            break;
        case JointCategory::eJOINT_ELB_POS:
            oJointClient.setPosELB(value);
            pAmyClient->sendJointCommand();
            break;
        case JointCategory::eJOINT_HWRI_POS:
            oJointClient.setPosHW(value);
            pAmyClient->sendJointCommand();
            break;
        case JointCategory::eJOINT_VWRI_POS:
            oJointClient.setPosVW(value);
            pAmyClient->sendJointCommand();
            break;
            
        default:
            LOG4CXX_ERROR(logger, "AmyConnector: joint request not available!");        
            bsent = false;
            break;
    }
    return bsent;
}

bool AmyConnector::sendAxisCommand(int action, float value)
{    
    bool bsent = true;
    
    AxisClient& oAxisClient = pAmyClient->getAxisClient();
    switch (action)
    {
        // axis speeds
        case AxisCategory::eAXIS_PAN_SPEED:
            oAxisClient.panSpeed(value);
            pAmyClient->sendAxisCommand();
            break;
        case AxisCategory::eAXIS_TILT_SPEED:
            oAxisClient.tiltSpeed(value);
            pAmyClient->sendAxisCommand();
            break;
        case AxisCategory::eAXIS_RAD_SPEED:
            oAxisClient.radialSpeed(value);
            pAmyClient->sendAxisCommand();
            break;        
        // axis positions
        case AxisCategory::eAXIS_PAN_POS:            
            oAxisClient.movePan(value);
            pAmyClient->sendAxisCommand();
            break;
        case AxisCategory::eAXIS_TILT_POS:
            oAxisClient.moveTilt(value);
            pAmyClient->sendAxisCommand();
            break;
        case AxisCategory::eAXIS_RAD_POS:
            oAxisClient.moveRadius(value);
            pAmyClient->sendAxisCommand();
            break;
                        
        default:
            LOG4CXX_ERROR(logger, "AmyConnector: axis request not available!");        
            bsent = false;
            break;
    }
    return bsent;
}

bool AmyConnector::sendCyclicCommand(int action, float value)
{    
    bool bsent = true;
    
    CyclicClient& oCyclicClient = pAmyClient->getCyclicClient();
    switch (action)
    {
        // pan cyclic moves
        case CyclicCategory::eCYCLIC_PAN_FREQ:
            oCyclicClient.panFrequency(value);
            pAmyClient->sendCyclicCommand();
            break;
        case CyclicCategory::eCYCLIC_PAN_AMP:
            oCyclicClient.panAmplitude(value);
            pAmyClient->sendCyclicCommand();
            break;
        case CyclicCategory::eCYCLIC_PAN_TRIGGER:
            oCyclicClient.panTrigger();
            pAmyClient->sendCyclicCommand();
            break;
        case CyclicCategory::eCYCLIC_PAN_STOP:            
            oCyclicClient.panStop();
            pAmyClient->sendCyclicCommand();
            break;
        // tilt cyclic moves
        case CyclicCategory::eCYCLIC_TILT_FREQ:
            oCyclicClient.tiltFrequency(value);
            pAmyClient->sendCyclicCommand();
            break;
        case CyclicCategory::eCYCLIC_TILT_AMP:
            oCyclicClient.tiltAmplitude(value);
            pAmyClient->sendCyclicCommand();
            break;
        case CyclicCategory::eCYCLIC_TILT_TRIGGER:
            oCyclicClient.tiltTrigger();
            pAmyClient->sendCyclicCommand();
            break;
        case CyclicCategory::eCYCLIC_TILT_STOP:            
            oCyclicClient.tiltStop();
            pAmyClient->sendCyclicCommand();
            break;
                        
        default:
            LOG4CXX_ERROR(logger, "AmyConnector: cyclic request not available!");        
            bsent = false;
            break;
    }
    return bsent;
}

bool AmyConnector::sendOtherCommand(int action, float value)
{    
    bool bsent = true;
    
    OtherClient& oOtherClient = pAmyClient->getOtherClient();
    switch (action)
    {
        // other commands
        case OtherCategory::eOTHER_ARM_STOP:
            pAmyClient->toDoCommand();
            break;
        case OtherCategory::eOTHER_KEEP_TILT:
            oOtherClient.keepTilt(1);
            pAmyClient->sendOtherCommand();
            break;
        case OtherCategory::eOTHER_AMY_END:
            oOtherClient.endAmy();
            pAmyClient->sendOtherCommand();
            break;
                                    
        default:
            LOG4CXX_ERROR(logger, "AmyConnector: other request not available!");        
            bsent = false;
            break;
    }
    return bsent;
}
}