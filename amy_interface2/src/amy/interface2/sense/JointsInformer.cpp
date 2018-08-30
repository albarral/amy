/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/sense/JointsInformer.h"
#include "amy/interface2/ArmNode.h"
#include "amy/interface2/channels/JointsSection.h"
#include "tron/topics/RobotNodes.h"
#include "tron/topics/Topic.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr JointsInformer::logger(Logger::getLogger("amy.interface"));

JointsInformer::JointsInformer()
{    
    // set topics for arm joints sense
    int node = tron::RobotNodes::eNODE_ARM;
    int section = ArmNode2::eSECTION_JOINTS;
    int type = tron::Topic::eTYPE_SENSOR;
    
    tron::Topic oTopic;
    ArmNode2 oArmNode;
    // for each channel in section
    for (int channel=0; channel<JointsSection::eJOINTS_DIM; channel++)
    {
        // set its topic 
        oTopic.set(node, section, channel, type);
        // and add a channel writer for it
        if (oArmNode.buildTopicName(oTopic))
            oComsSender.addChannel(oTopic.getTopicName());            
    }
    
    // store channel pointers for faster access
    pHSChannel = oComsSender.getChannel(JointsSection::eJOINTS_HS);
    pVSChannel = oComsSender.getChannel(JointsSection::eJOINTS_VS);
    pELBChannel = oComsSender.getChannel(JointsSection::eJOINTS_ELB);
    pHWRIChannel = oComsSender.getChannel(JointsSection::eJOINTS_HWRI);
    pVWRIChannel = oComsSender.getChannel(JointsSection::eJOINTS_VWRI);    
}

//JointsInformer::~JointsInformer()
//{    
//}

bool JointsInformer::sendHS(float value)
{    
    LOG4CXX_DEBUG(logger, "JointsInformer: send HS > " << std::to_string(value));
    return pHSChannel->sendMessage(std::to_string(value));
}

bool JointsInformer::sendVS(float value)
{    
    LOG4CXX_DEBUG(logger, "JointsInformer: send VS > " << std::to_string(value));
    return pVSChannel->sendMessage(std::to_string(value));
}

bool JointsInformer::sendELB(float value)
{    
    LOG4CXX_DEBUG(logger, "JointsInformer: send ELB > " << std::to_string(value));
    return pELBChannel->sendMessage(std::to_string(value));
}

bool JointsInformer::sendHWRI(float value)
{    
    LOG4CXX_DEBUG(logger, "JointsInformer: send HWRI > " << std::to_string(value));
    return pHWRIChannel->sendMessage(std::to_string(value));
}

bool JointsInformer::sendVWRI(float value)
{    
    LOG4CXX_DEBUG(logger, "JointsInformer: send VWRI > " << std::to_string(value));
    return pVWRIChannel->sendMessage(std::to_string(value));
}
}