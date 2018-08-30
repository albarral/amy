/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/sense/JointsListener.h"
#include "amy/interface2/ArmNode.h"
#include "amy/interface2/channels/JointsSection.h"
#include "tron/topics/RobotNodes.h"
#include "tron/topics/Topic.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr JointsListener::logger(Logger::getLogger("amy.interface"));

JointsListener::JointsListener()
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
        // and add a channel reader for it
        if (oArmNode.buildTopicName(oTopic))
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

//JointsListener::~JointsListener()
//{    
//}

bool JointsListener::senseHS(float& value)
{    
    // if hs info received, get it
    if (pHSChannel->hasNew()) 
    {
        value = std::stof(pHSChannel->getMessage());
        LOG4CXX_DEBUG(logger, "JointsListener: sense HS > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool JointsListener::senseVS(float& value)
{    
    // if vs info received, get it
    if (pVSChannel->hasNew())
    {
        value = std::stof(pVSChannel->getMessage());
        LOG4CXX_DEBUG(logger, "JointsListener: sense VS > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool JointsListener::senseELB(float& value)
{    
    // if elbow info received, get it
    if (pELBChannel->hasNew())
    {
        value = std::stof(pELBChannel->getMessage());
        LOG4CXX_DEBUG(logger, "JointsListener: sense ELB > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool JointsListener::senseHWRI(float& value)
{    
    // if h wrist info received, get it
    if (pHWRIChannel->hasNew())
    {
        value = std::stof(pHWRIChannel->getMessage());
        LOG4CXX_DEBUG(logger, "JointsListener: sense HWRI > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool JointsListener::senseVWRI(float& value)
{    
    // if v wrist info received, get it
    if (pVWRIChannel->hasNew())
    {
        value = std::stof(pVWRIChannel->getMessage());
        LOG4CXX_DEBUG(logger, "JointsListener: sense VWRI > " << std::to_string(value));
        return true;
    }
    else
        return false;
}
}