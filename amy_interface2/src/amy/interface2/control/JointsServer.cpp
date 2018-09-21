/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/control/JointsServer.h"
#include "amy/interface2/ArmNode.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr JointsServer::logger2(Logger::getLogger("amy.interface.control"));

JointsServer::JointsServer()
{    
    ArmNode2 oArmNode;
    // set topics for arm joints control
    tron::SectionServer::tune4Node(oArmNode, ArmNode2::eSECTION_JOINTS);

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

//JointsServer::~JointsServer()
//{    
//}

bool JointsServer::getHS(float& value)
{    
    // if hs command received, get it
    if (pHSChannel->hasNew()) 
    {
        value = std::stof(pHSChannel->getMessage());
        LOG4CXX_DEBUG(logger2, "JointsServer: get HS > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool JointsServer::getVS(float& value)
{    
    // if vs command received, get it
    if (pVSChannel->hasNew())
    {
        value = std::stof(pVSChannel->getMessage());
        LOG4CXX_DEBUG(logger2, "JointsServer: get VS > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool JointsServer::getELB(float& value)
{    
    // if elbow command received, get it
    if (pELBChannel->hasNew())
    {
        value = std::stof(pELBChannel->getMessage());
        LOG4CXX_DEBUG(logger2, "JointsServer: get ELB > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool JointsServer::getHWRI(float& value)
{    
    // if h wrist command received, get it
    if (pHWRIChannel->hasNew())
    {
        value = std::stof(pHWRIChannel->getMessage());
        LOG4CXX_DEBUG(logger2, "JointsServer: get HWRI > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool JointsServer::getVWRI(float& value)
{    
    // if v wrist command received, get it
    if (pVWRIChannel->hasNew())
    {
        value = std::stof(pVWRIChannel->getMessage());
        LOG4CXX_DEBUG(logger2, "JointsServer: get VWRI > " << std::to_string(value));
        return true;
    }
    else
        return false;
}
}