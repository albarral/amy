/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/control/AxesClient.h"
#include "amy/interface2/ArmNode.h"
#include "tron/topics/RobotNodes.h"
#include "tron/topics/Topic.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AxesClient::logger(Logger::getLogger("amy.interface"));

AxesClient::AxesClient()
{    
    // set topics for arm axes control
    int node = tron::RobotNodes::eNODE_ARM;
    int section = ArmNode2::eSECTION_AXES;
    int type = tron::Topic::eTYPE_CONTROL;
    
    tron::Topic oTopic;
    ArmNode2 oArmNode;
    // for each channel in section
    for (int channel=0; channel<ArmNode2::eAXES_DIM; channel++)
    {
        // set its topic 
        oTopic.set(node, section, channel, type);
        // and add a channel writer for it
        if (oArmNode.buildTopicName(oTopic))
            oComsSender.addChannel(oTopic.getTopicName());            
    }
    
    // store channel pointers for faster access
    pPanChannel = oComsSender.getChannel(ArmNode2::eAXES_PAN);
    pTiltChannel = oComsSender.getChannel(ArmNode2::eAXES_TILT);
    pRadialChannel = oComsSender.getChannel(ArmNode2::eAXES_RAD);
    pPanSpeedChannel = oComsSender.getChannel(ArmNode2::eAXES_PAN_SPEED);
    pTiltSpeedChannel = oComsSender.getChannel(ArmNode2::eAXES_TILT_SPEED);    
    pRadialSpeedChannel = oComsSender.getChannel(ArmNode2::eAXES_RAD_SPEED);    
    pKeepTiltChannel = oComsSender.getChannel(ArmNode2::eAXES_KEEP_TILT);    
}

//AxesClient::~AxesClient()
//{    
//}

bool AxesClient::setPan(float value)
{    
    LOG4CXX_DEBUG(logger, "AxesClient: set Pan > " << std::to_string(value));
    return pPanChannel->sendMessage(std::to_string(value));
}

bool AxesClient::setTilt(float value)
{    
    LOG4CXX_DEBUG(logger, "AxesClient: set Tilt > " << std::to_string(value));
    return pTiltChannel->sendMessage(std::to_string(value));
}

bool AxesClient::setRadial(float value)
{    
    LOG4CXX_DEBUG(logger, "AxesClient: set Radial > " << std::to_string(value));
    return pRadialChannel->sendMessage(std::to_string(value));
}

bool AxesClient::setPanSpeed(float value)
{    
    LOG4CXX_DEBUG(logger, "AxesClient: set PanSpeed > " << std::to_string(value));
    return pPanSpeedChannel->sendMessage(std::to_string(value));
}

bool AxesClient::setTiltSpeed(float value)
{    
    LOG4CXX_DEBUG(logger, "AxesClient: set TiltSpeed > " << std::to_string(value));
    return pTiltSpeedChannel->sendMessage(std::to_string(value));
}

bool AxesClient::setRadialSpeed(float value)
{    
    LOG4CXX_DEBUG(logger, "AxesClient: set RadialSpeed > " << std::to_string(value));
    return pRadialSpeedChannel->sendMessage(std::to_string(value));
}

bool AxesClient::keepTilt()
{    
    LOG4CXX_DEBUG(logger, "AxesClient: keep tilt");
    return pKeepTiltChannel->sendMessage(std::to_string(1));
}
}