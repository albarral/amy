/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/JointsClient.h"
#include "amy/interface2/ArmNode.h"
#include "amy/interface2/channels/JointsSection.h"
#include "tron/topics/RobotNodes.h"
#include "tron/topics/Topic.h"

using namespace log4cxx;

namespace amy
{
JointsClient::JointsClient()
{    
    // define topic elements for the joints section
    int node = tron::RobotNodes::eNODE_ARM;
    int section = ArmNode2::eSECTION_JOINTS;
    int type = tron::Topic::eTYPE_CONTROL;
    
    tron::Topic oTopic;
    ArmNode2 oArmNode;
    // for each channel in the joints section
    for (int channel=0; channel<JointsSection::eJOINTS_DIM; channel++)
    {
        // set proper topic 
        oTopic.set(node, section, channel, type);
        // and add a channel for it
        if (oArmNode.buildTopic(oTopic))
            tron::ComsSender::addChannel(oTopic.getTopicName());            
    }
}

//JointsClient::~JointsClient()
//{    
//}

bool JointsClient::setHS(float value)
{    
    LOG4CXX_DEBUG(logger, "JointsClient: set HS > " << std::to_string(value));
    return getChannel(JointsSection::eJOINTS_HS)->sendMessage(std::to_string(value));
}

bool JointsClient::setVS(float value)
{    
    LOG4CXX_DEBUG(logger, "JointsClient: set VS > " << std::to_string(value));
    return getChannel(JointsSection::eJOINTS_VS)->sendMessage(std::to_string(value));
}

bool JointsClient::setELB(float value)
{    
    LOG4CXX_DEBUG(logger, "JointsClient: set ELB > " << std::to_string(value));
    return getChannel(JointsSection::eJOINTS_ELB)->sendMessage(std::to_string(value));
}

bool JointsClient::setHWRI(float value)
{    
    LOG4CXX_DEBUG(logger, "JointsClient: set HWRI > " << std::to_string(value));
    return getChannel(JointsSection::eJOINTS_HWRI)->sendMessage(std::to_string(value));
}

bool JointsClient::setVWRI(float value)
{    
    LOG4CXX_DEBUG(logger, "JointsClient: set VWRI > " << std::to_string(value));
    return getChannel(JointsSection::eJOINTS_VWRI)->sendMessage(std::to_string(value));
}
}