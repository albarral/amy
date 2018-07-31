/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/control/JointsClient.h"
#include "amy/interface2/ArmNode.h"
#include "amy/interface2/channels/JointsSection.h"
#include "tron/topics/RobotNodes.h"
#include "tron/topics/Topic.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr JointsClient::logger(Logger::getLogger("amy.interface"));

JointsClient::JointsClient()
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
        // and add a channel writer for it
        if (oArmNode.buildTopic(oTopic))
            oComsSender.addChannel(oTopic.getTopicName());            
    }
    
    // store channel pointers for faster access
    pHSChannel = oComsSender.getChannel(JointsSection::eJOINTS_HS);
    pVSChannel = oComsSender.getChannel(JointsSection::eJOINTS_VS);
    pELBChannel = oComsSender.getChannel(JointsSection::eJOINTS_ELB);
    pHWRIChannel = oComsSender.getChannel(JointsSection::eJOINTS_HWRI);
    pVWRIChannel = oComsSender.getChannel(JointsSection::eJOINTS_VWRI);    
}

//JointsClient::~JointsClient()
//{    
//}

bool JointsClient::setHS(float value)
{    
    LOG4CXX_DEBUG(logger, "JointsClient: set HS > " << std::to_string(value));
    return pHSChannel->sendMessage(std::to_string(value));
}

bool JointsClient::setVS(float value)
{    
    LOG4CXX_DEBUG(logger, "JointsClient: set VS > " << std::to_string(value));
    return pVSChannel->sendMessage(std::to_string(value));
}

bool JointsClient::setELB(float value)
{    
    LOG4CXX_DEBUG(logger, "JointsClient: set ELB > " << std::to_string(value));
    return pELBChannel->sendMessage(std::to_string(value));
}

bool JointsClient::setHWRI(float value)
{    
    LOG4CXX_DEBUG(logger, "JointsClient: set HWRI > " << std::to_string(value));
    return pHWRIChannel->sendMessage(std::to_string(value));
}

bool JointsClient::setVWRI(float value)
{    
    LOG4CXX_DEBUG(logger, "JointsClient: set VWRI > " << std::to_string(value));
    return pVWRIChannel->sendMessage(std::to_string(value));
}
}