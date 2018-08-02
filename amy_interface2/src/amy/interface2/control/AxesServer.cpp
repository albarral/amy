/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/control/AxesServer.h"
#include "amy/interface2/ArmNode.h"
#include "amy/interface2/channels/AxesSection.h"
#include "tron/topics/RobotNodes.h"
#include "tron/topics/Topic.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AxesServer::logger(Logger::getLogger("amy.interface"));

AxesServer::AxesServer()
{    
    // set topics for arm joints control
    int node = tron::RobotNodes::eNODE_ARM;
    int section = ArmNode2::eSECTION_AXES;
    int type = tron::Topic::eTYPE_CONTROL;
    
    tron::Topic oTopic;
    ArmNode2 oArmNode;
    // for each channel in section
    for (int channel=0; channel<AxesSection::eAXES_DIM; channel++)
    {
        // set its topic 
        oTopic.set(node, section, channel, type);
        // and add a channel reader for it
        if (oArmNode.buildTopic(oTopic))
            oComsReceiver.addChannel(oTopic.getTopicName());            
    }
    
    // connect all readers
    oComsReceiver.connect();
    
    // store channel pointers for faster access
    pPanChannel = oComsReceiver.getChannel(AxesSection::eAXES_PAN);
    pTiltChannel = oComsReceiver.getChannel(AxesSection::eAXES_TILT);
    pRadialChannel = oComsReceiver.getChannel(AxesSection::eAXES_RAD);
    pPanSpeedChannel = oComsReceiver.getChannel(AxesSection::eAXES_PAN_SPEED);
    pTiltSpeedChannel = oComsReceiver.getChannel(AxesSection::eAXES_TILT_SPEED);    
    pRadialSpeedChannel = oComsReceiver.getChannel(AxesSection::eAXES_RAD_SPEED);    
    pKeepTiltChannel = oComsReceiver.getChannel(AxesSection::eAXES_KEEP_TILT);    
}

//AxesServer::~AxesServer()
//{    
//}

bool AxesServer::getPan(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pPanChannel->getMessages(listMessages) != 0)
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, "AxesServer: get Pan > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool AxesServer::getTilt(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pTiltChannel->getMessages(listMessages))
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, "AxesServer: get Tilt > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool AxesServer::getRadial(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pRadialChannel->getMessages(listMessages))
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, "AxesServer: get Radial > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool AxesServer::getPanSpeed(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pPanSpeedChannel->getMessages(listMessages))
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, "AxesServer: get PanSpeed > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool AxesServer::getTiltSpeed(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pTiltSpeedChannel->getMessages(listMessages))
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, "AxesServer: get TiltSpeed > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool AxesServer::getRadialSpeed(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pRadialSpeedChannel->getMessages(listMessages))
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, "AxesServer: get RadialSpeed > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool AxesServer::getKeepTilt(bool& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pKeepTiltChannel->getMessages(listMessages))
    {
        value = (bool)std::stoi(listMessages.back());
        LOG4CXX_DEBUG(logger, "AxesServer: get keep tilt > " << std::to_string(value));
        return true;
    }
    else
        return false;
}
}