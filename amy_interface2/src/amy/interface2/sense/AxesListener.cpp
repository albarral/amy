/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/sense/AxesListener.h"
#include "amy/interface2/ArmNode.h"
#include "tron/topics/RobotNodes.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AxesListener::logger(Logger::getLogger("amy.interface.sense"));

AxesListener::AxesListener()
{    
    // set topics for arm axes sense
    ArmNode2 oArmNode;
    tron::SectionListener::tune4Node(tron::RobotNodes::eNODE_ARM, ArmNode2::eSECTION_AXES, oArmNode);

    if (isTuned())
    {
        // store channel pointers for faster access
        pPanChannel = oComsReceiver.getChannel(ArmNode2::eAXES_PAN);
        pTiltChannel = oComsReceiver.getChannel(ArmNode2::eAXES_TILT);
        pRadialChannel = oComsReceiver.getChannel(ArmNode2::eAXES_RAD);
        pPanSpeedChannel = oComsReceiver.getChannel(ArmNode2::eAXES_PAN_SPEED);
        pTiltSpeedChannel = oComsReceiver.getChannel(ArmNode2::eAXES_TILT_SPEED);    
        pRadialSpeedChannel = oComsReceiver.getChannel(ArmNode2::eAXES_RAD_SPEED);    
    }
}

//AxesListener::~AxesListener()
//{    
//}

bool AxesListener::sensePan(float& value)
{    
    // if info received, get it
    if (pPanChannel->hasNew()) 
    {
        value = std::stof(pPanChannel->getMessage());
        LOG4CXX_DEBUG(logger, "AxesListener: sense Pan > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool AxesListener::senseTilt(float& value)
{    
    // if info received, get it
    if (pTiltChannel->hasNew())
    {
        value = std::stof(pTiltChannel->getMessage());
        LOG4CXX_DEBUG(logger, "AxesListener: sense Tilt > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool AxesListener::senseRadial(float& value)
{    
    // if info received, get it
    if (pRadialChannel->hasNew())
    {
        value = std::stof(pRadialChannel->getMessage());
        LOG4CXX_DEBUG(logger, "AxesListener: sense Radial > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool AxesListener::sensePanSpeed(float& value)
{    
    // if info received, get it
    if (pPanSpeedChannel->hasNew())
    {
        value = std::stof(pPanSpeedChannel->getMessage());
        LOG4CXX_DEBUG(logger, "AxesListener: sense PanSpeed > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool AxesListener::senseTiltSpeed(float& value)
{    
    // if info received, get it
    if (pTiltSpeedChannel->hasNew())
    {
        value = std::stof(pTiltSpeedChannel->getMessage());
        LOG4CXX_DEBUG(logger, "AxesListener: sense TiltSpeed > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool AxesListener::senseRadialSpeed(float& value)
{    
    // if info received, get it
    if (pRadialSpeedChannel->hasNew())
    {
        value = std::stof(pRadialSpeedChannel->getMessage());
        LOG4CXX_DEBUG(logger, "AxesListener: sense RadialSpeed > " << std::to_string(value));
        return true;
    }
    else
        return false;
}
}