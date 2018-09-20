/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/sense/AxesInformer.h"
#include "amy/interface2/ArmNode.h"
#include "tron/topics/RobotNodes.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AxesInformer::logger(Logger::getLogger("amy.interface.sense"));

AxesInformer::AxesInformer()
{    
    // set topics for arm axes sense
    ArmNode2 oArmNode;
    tron::SectionInformer::tune4Node(tron::RobotNodes::eNODE_ARM, ArmNode2::eSECTION_AXES, oArmNode);

    if (isTuned())
    {
        // store channel pointers for faster access
        pPanChannel = oComsSender.getChannel(ArmNode2::eAXES_PAN);
        pTiltChannel = oComsSender.getChannel(ArmNode2::eAXES_TILT);
        pRadialChannel = oComsSender.getChannel(ArmNode2::eAXES_RAD);
        pPanSpeedChannel = oComsSender.getChannel(ArmNode2::eAXES_PAN_SPEED);
        pTiltSpeedChannel = oComsSender.getChannel(ArmNode2::eAXES_TILT_SPEED);    
        pRadialSpeedChannel = oComsSender.getChannel(ArmNode2::eAXES_RAD_SPEED);    
    }
}

//AxesInformer::~AxesInformer()
//{    
//}

bool AxesInformer::sendPan(float value)
{    
    LOG4CXX_DEBUG(logger, "AxesInformer: send Pan > " << std::to_string(value));
    return pPanChannel->sendMessage(std::to_string(value));
}

bool AxesInformer::sendTilt(float value)
{    
    LOG4CXX_DEBUG(logger, "AxesInformer: send Tilt > " << std::to_string(value));
    return pTiltChannel->sendMessage(std::to_string(value));
}

bool AxesInformer::sendRadial(float value)
{    
    LOG4CXX_DEBUG(logger, "AxesInformer: send Radial > " << std::to_string(value));
    return pRadialChannel->sendMessage(std::to_string(value));
}

bool AxesInformer::sendPanSpeed(float value)
{    
    LOG4CXX_DEBUG(logger, "AxesInformer: send PanSpeed > " << std::to_string(value));
    return pPanSpeedChannel->sendMessage(std::to_string(value));
}

bool AxesInformer::sendTiltSpeed(float value)
{    
    LOG4CXX_DEBUG(logger, "AxesInformer: send TiltSpeed > " << std::to_string(value));
    return pTiltSpeedChannel->sendMessage(std::to_string(value));
}

bool AxesInformer::sendRadialSpeed(float value)
{    
    LOG4CXX_DEBUG(logger, "AxesInformer: send RadialSpeed > " << std::to_string(value));
    return pRadialSpeedChannel->sendMessage(std::to_string(value));
}
}