/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/control/AxesServer.h"
#include "amy/interface2/ArmNode.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AxesServer::logger2(Logger::getLogger("amy.interface.control"));

AxesServer::AxesServer()
{    
    ArmNode2 oArmNode;
    // set topics for arm axes control
    tron::SectionServer::tune4Node(oArmNode, ArmNode2::eSECTION_AXES);

    if (isTuned())
    {
        // store channel pointers for faster access
        pPanChannel = oComsReceiver.getChannel(ArmNode2::eAXES_PAN);
        pTiltChannel = oComsReceiver.getChannel(ArmNode2::eAXES_TILT);
        pRadialChannel = oComsReceiver.getChannel(ArmNode2::eAXES_RAD);
        pPanSpeedChannel = oComsReceiver.getChannel(ArmNode2::eAXES_PAN_SPEED);
        pTiltSpeedChannel = oComsReceiver.getChannel(ArmNode2::eAXES_TILT_SPEED);    
        pRadialSpeedChannel = oComsReceiver.getChannel(ArmNode2::eAXES_RAD_SPEED);    
        pKeepTiltChannel = oComsReceiver.getChannel(ArmNode2::eAXES_KEEP_TILT);    
    }
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
        LOG4CXX_DEBUG(logger2, "AxesServer: get Pan > " << std::to_string(value));
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
        LOG4CXX_DEBUG(logger2, "AxesServer: get Tilt > " << std::to_string(value));
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
        LOG4CXX_DEBUG(logger2, "AxesServer: get Radial > " << std::to_string(value));
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
        LOG4CXX_DEBUG(logger2, "AxesServer: get PanSpeed > " << std::to_string(value));
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
        LOG4CXX_DEBUG(logger2, "AxesServer: get TiltSpeed > " << std::to_string(value));
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
        LOG4CXX_DEBUG(logger2, "AxesServer: get RadialSpeed > " << std::to_string(value));
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
        LOG4CXX_DEBUG(logger2, "AxesServer: get keep tilt > " << std::to_string(value));
        return true;
    }
    else
        return false;
}
}