/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/control/JointsServer.h"
#include "amy/interface2/ArmNode.h"
#include "amy/interface2/channels/JointsSection.h"
#include "tron/topics/RobotNodes.h"
#include "tron/topics/Topic.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr JointsServer::logger(Logger::getLogger("amy.interface"));

JointsServer::JointsServer()
{    
    // set topics for arm joints control
    int node = tron::RobotNodes::eNODE_ARM;
    int section = ArmNode2::eSECTION_JOINTS;
    int type = tron::Topic::eTYPE_CONTROL;
    
    tron::Topic oTopic;
    ArmNode2 oArmNode;
    // for each channel in section
    for (int channel=0; channel<JointsSection::eJOINTS_DIM; channel++)
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
    pHSChannel = oComsReceiver.getChannel(JointsSection::eJOINTS_HS);
    pVSChannel = oComsReceiver.getChannel(JointsSection::eJOINTS_VS);
    pELBChannel = oComsReceiver.getChannel(JointsSection::eJOINTS_ELB);
    pHWRIChannel = oComsReceiver.getChannel(JointsSection::eJOINTS_HWRI);
    pVWRIChannel = oComsReceiver.getChannel(JointsSection::eJOINTS_VWRI);    
}

//JointsServer::~JointsServer()
//{    
//}

bool JointsServer::getHS(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pHSChannel->getMessages(listMessages) != 0)
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, "JointsServer: get HS > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool JointsServer::getVS(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pVSChannel->getMessages(listMessages))
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, "JointsServer: get VS > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool JointsServer::getELB(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pELBChannel->getMessages(listMessages))
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, "JointsServer: get ELB > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool JointsServer::getHWRI(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pHWRIChannel->getMessages(listMessages))
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, "JointsServer: get HWRI > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool JointsServer::getVWRI(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pVWRIChannel->getMessages(listMessages))
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, "JointsServer: get VWRI > " << std::to_string(value));
        return true;
    }
    else
        return false;
}
}