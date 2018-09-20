/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/control/AxesClient.h"
#include "amy/interface2/ArmNode.h"
#include "tron/topics/RobotNodes.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AxesClient::logger2(Logger::getLogger("amy.interface.control"));

AxesClient::AxesClient()
{    
    ArmNode2 oArmNode;
    // set topics for arm joints control
    tron::SectionClient::tune4Node(tron::RobotNodes::eNODE_ARM, ArmNode2::eSECTION_AXES, oArmNode);

    if (isTuned())
    {
        // store channel pointers for faster access
        pPanChannel = oComsSender.getChannel(ArmNode2::eAXES_PAN);
        pTiltChannel = oComsSender.getChannel(ArmNode2::eAXES_TILT);
        pRadialChannel = oComsSender.getChannel(ArmNode2::eAXES_RAD);
        pPanSpeedChannel = oComsSender.getChannel(ArmNode2::eAXES_PAN_SPEED);
        pTiltSpeedChannel = oComsSender.getChannel(ArmNode2::eAXES_TILT_SPEED);    
        pRadialSpeedChannel = oComsSender.getChannel(ArmNode2::eAXES_RAD_SPEED);    
        pKeepTiltChannel = oComsSender.getChannel(ArmNode2::eAXES_KEEP_TILT);    
    }
}

//AxesClient::~AxesClient()
//{    
//}

bool AxesClient::setPan(float value)
{    
    LOG4CXX_DEBUG(logger2, "AxesClient: set Pan > " << std::to_string(value));
    return pPanChannel->sendMessage(std::to_string(value));
}

bool AxesClient::setTilt(float value)
{    
    LOG4CXX_DEBUG(logger2, "AxesClient: set Tilt > " << std::to_string(value));
    return pTiltChannel->sendMessage(std::to_string(value));
}

bool AxesClient::setRadial(float value)
{    
    LOG4CXX_DEBUG(logger2, "AxesClient: set Radial > " << std::to_string(value));
    return pRadialChannel->sendMessage(std::to_string(value));
}

bool AxesClient::setPanSpeed(float value)
{    
    LOG4CXX_DEBUG(logger2, "AxesClient: set PanSpeed > " << std::to_string(value));
    return pPanSpeedChannel->sendMessage(std::to_string(value));
}

bool AxesClient::setTiltSpeed(float value)
{    
    LOG4CXX_DEBUG(logger2, "AxesClient: set TiltSpeed > " << std::to_string(value));
    return pTiltSpeedChannel->sendMessage(std::to_string(value));
}

bool AxesClient::setRadialSpeed(float value)
{    
    LOG4CXX_DEBUG(logger2, "AxesClient: set RadialSpeed > " << std::to_string(value));
    return pRadialSpeedChannel->sendMessage(std::to_string(value));
}

bool AxesClient::keepTilt()
{    
    LOG4CXX_DEBUG(logger2, "AxesClient: keep tilt");
    return pKeepTiltChannel->sendMessage(std::to_string(1));
}
}