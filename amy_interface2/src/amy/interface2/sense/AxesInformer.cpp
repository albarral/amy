/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/sense/AxesInformer.h"
#include "amy/interface2/ArmNode.h"
#include "amy/interface2/channels/AxesSection.h"
#include "tron/topics/RobotNodes.h"
#include "tron/topics/Topic.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AxesInformer::logger(Logger::getLogger("amy.interface"));

AxesInformer::AxesInformer()
{    
    // set topics for arm axes sense
    int node = tron::RobotNodes::eNODE_ARM;
    int section = ArmNode2::eSECTION_AXES;
    int type = tron::Topic::eTYPE_SENSOR;
    
    tron::Topic oTopic;
    ArmNode2 oArmNode;
    // for each channel in section
    for (int channel=0; channel<AxesSection::eAXES_DIM; channel++)
    {
        // set its topic 
        oTopic.set(node, section, channel, type);
        // and add a channel writer for it
        if (oArmNode.buildTopicName(oTopic))
            oComsSender.addChannel(oTopic.getTopicName());            
    }
    
    // store channel pointers for faster access
    pPanChannel = oComsSender.getChannel(AxesSection::eAXES_PAN);
    pTiltChannel = oComsSender.getChannel(AxesSection::eAXES_TILT);
    pRadialChannel = oComsSender.getChannel(AxesSection::eAXES_RAD);
    pPanSpeedChannel = oComsSender.getChannel(AxesSection::eAXES_PAN_SPEED);
    pTiltSpeedChannel = oComsSender.getChannel(AxesSection::eAXES_TILT_SPEED);    
    pRadialSpeedChannel = oComsSender.getChannel(AxesSection::eAXES_RAD_SPEED);    
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