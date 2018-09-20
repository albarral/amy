/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/sense/JointsInformer.h"
#include "amy/interface2/ArmNode.h"
#include "tron/topics/RobotNodes.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr JointsInformer::logger2(Logger::getLogger("amy.interface.sense"));

JointsInformer::JointsInformer()
{    
    // set topics for arm joints sense
    ArmNode2 oArmNode;
    tron::SectionInformer::tune4Node(tron::RobotNodes::eNODE_ARM, ArmNode2::eSECTION_JOINTS, oArmNode);

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

//JointsInformer::~JointsInformer()
//{    
//}

bool JointsInformer::sendHS(float value)
{    
    LOG4CXX_DEBUG(logger2, "JointsInformer: send HS > " << std::to_string(value));
    return pHSChannel->sendMessage(std::to_string(value));
}

bool JointsInformer::sendVS(float value)
{    
    LOG4CXX_DEBUG(logger2, "JointsInformer: send VS > " << std::to_string(value));
    return pVSChannel->sendMessage(std::to_string(value));
}

bool JointsInformer::sendELB(float value)
{    
    LOG4CXX_DEBUG(logger2, "JointsInformer: send ELB > " << std::to_string(value));
    return pELBChannel->sendMessage(std::to_string(value));
}

bool JointsInformer::sendHWRI(float value)
{    
    LOG4CXX_DEBUG(logger2, "JointsInformer: send HWRI > " << std::to_string(value));
    return pHWRIChannel->sendMessage(std::to_string(value));
}

bool JointsInformer::sendVWRI(float value)
{    
    LOG4CXX_DEBUG(logger2, "JointsInformer: send VWRI > " << std::to_string(value));
    return pVWRIChannel->sendMessage(std::to_string(value));
}
}