/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/sense/JointsListener.h"
#include "amy/interface2/ArmNode.h"
#include "tron/topics/RobotNodes.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr JointsListener::logger2(Logger::getLogger("amy.interface.sense"));

JointsListener::JointsListener()
{    
    // set topics for arm joints sense
    ArmNode2 oArmNode;
    tron::SectionListener::tune4Node(tron::RobotNodes::eNODE_ARM, ArmNode2::eSECTION_JOINTS, oArmNode);

    if (isTuned())
    {
        // store channel pointers for faster access
        pHSChannel = oComsReceiver.getChannel(ArmNode2::eJOINTS_HS);
        pVSChannel = oComsReceiver.getChannel(ArmNode2::eJOINTS_VS);
        pELBChannel = oComsReceiver.getChannel(ArmNode2::eJOINTS_ELB);
        pHWRIChannel = oComsReceiver.getChannel(ArmNode2::eJOINTS_HWRI);
        pVWRIChannel = oComsReceiver.getChannel(ArmNode2::eJOINTS_VWRI);    
    }
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
        LOG4CXX_DEBUG(logger2, "JointsListener: sense HS > " << std::to_string(value));
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
        LOG4CXX_DEBUG(logger2, "JointsListener: sense VS > " << std::to_string(value));
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
        LOG4CXX_DEBUG(logger2, "JointsListener: sense ELB > " << std::to_string(value));
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
        LOG4CXX_DEBUG(logger2, "JointsListener: sense HWRI > " << std::to_string(value));
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
        LOG4CXX_DEBUG(logger2, "JointsListener: sense VWRI > " << std::to_string(value));
        return true;
    }
    else
        return false;
}
}