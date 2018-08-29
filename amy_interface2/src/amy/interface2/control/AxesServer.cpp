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
        if (oArmNode.buildTopicName(oTopic))
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
    // if pan command received, get it
    if (pPanChannel->hasNew())
    {
        value = std::stof(pPanChannel->getMessage());
        LOG4CXX_DEBUG(logger, "AxesServer: get Pan > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool AxesServer::getTilt(float& value)
{    
    // if tilt command received, get it
    if (pTiltChannel->hasNew())
    {
        value = std::stof(pTiltChannel->getMessage());
        LOG4CXX_DEBUG(logger, "AxesServer: get Tilt > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool AxesServer::getRadial(float& value)
{    
    // if radial command received, get it
    if (pRadialChannel->hasNew())
    {
        value = std::stof(pRadialChannel->getMessage());
        LOG4CXX_DEBUG(logger, "AxesServer: get Radial > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool AxesServer::getPanSpeed(float& value)
{    
    // if pan speed command received, get it
    if (pPanSpeedChannel->hasNew())
    {
        value = std::stof(pPanSpeedChannel->getMessage());
        LOG4CXX_DEBUG(logger, "AxesServer: get PanSpeed > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool AxesServer::getTiltSpeed(float& value)
{    
    // if tilt speed command received, get it
    if (pTiltSpeedChannel->hasNew())
    {
        value = std::stof(pTiltSpeedChannel->getMessage());
        LOG4CXX_DEBUG(logger, "AxesServer: get TiltSpeed > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool AxesServer::getRadialSpeed(float& value)
{    
    // if radial speed command received, get it
    if (pRadialSpeedChannel->hasNew())
    {
        value = std::stof(pRadialSpeedChannel->getMessage());
        LOG4CXX_DEBUG(logger, "AxesServer: get RadialSpeed > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool AxesServer::getKeepTilt(bool& value)
{    
    // if keep tilt command received, get it
    if (pKeepTiltChannel->hasNew())
    {
        value = (bool)std::stoi(pKeepTiltChannel->getMessage());
        LOG4CXX_DEBUG(logger, "AxesServer: get keep tilt > " << std::to_string(value));
        return true;
    }
    else
        return false;
}
}