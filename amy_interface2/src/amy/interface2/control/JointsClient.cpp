/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/control/JointsClient.h"
#include "amy/interface2/ArmNode.h"
#include "tron/topics/RobotNodes.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr JointsClient::logger2(Logger::getLogger("amy.interface.control"));

JointsClient::JointsClient()
{    
    ArmNode2 oArmNode;
    // set topics for arm joints control
    tron::SectionClient::tune4Node(tron::RobotNodes::eNODE_ARM, ArmNode2::eSECTION_JOINTS, oArmNode);

    if (isTuned())
    {
        // store channel pointers for faster access
        pHSChannel = oComsSender.getChannel(ArmNode2::eJOINTS_HS);
        pVSChannel = oComsSender.getChannel(ArmNode2::eJOINTS_VS);
        pELBChannel = oComsSender.getChannel(ArmNode2::eJOINTS_ELB);
        pHWRIChannel = oComsSender.getChannel(ArmNode2::eJOINTS_HWRI);
        pVWRIChannel = oComsSender.getChannel(ArmNode2::eJOINTS_VWRI);    
    }
}

//JointsClient::~JointsClient()
//{    
//}

bool JointsClient::setHS(float value)
{    
    LOG4CXX_DEBUG(logger2, "JointsClient: set HS > " << std::to_string(value));
    return pHSChannel->sendMessage(std::to_string(value));
}

bool JointsClient::setVS(float value)
{    
    LOG4CXX_DEBUG(logger2, "JointsClient: set VS > " << std::to_string(value));
    return pVSChannel->sendMessage(std::to_string(value));
}

bool JointsClient::setELB(float value)
{    
    LOG4CXX_DEBUG(logger2, "JointsClient: set ELB > " << std::to_string(value));
    return pELBChannel->sendMessage(std::to_string(value));
}

bool JointsClient::setHWRI(float value)
{    
    LOG4CXX_DEBUG(logger2, "JointsClient: set HWRI > " << std::to_string(value));
    return pHWRIChannel->sendMessage(std::to_string(value));
}

bool JointsClient::setVWRI(float value)
{    
    LOG4CXX_DEBUG(logger2, "JointsClient: set VWRI > " << std::to_string(value));
    return pVWRIChannel->sendMessage(std::to_string(value));
}
}