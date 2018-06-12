/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/publisher/AxisChannelPublisher.h"
#include "amy/interface/ArmNode.h"
#include "amy/interface/topics/AxisTopic.h"
#include "tron2/robot/RobotSystem.h"

using namespace log4cxx;

namespace amy
{
AxisChannelPublisher::AxisChannelPublisher()
{    
    int channel = ArmNode::eARM_AXES_CHANNEL;    
    tron2::ChannelPublisher::connect2Channel(tron2::RobotSystem::eNODE_ARM, channel, ArmNode::getTopic4Channel(channel));    
    pBusPan = 0;
    pBusTilt = 0;
    pBusRadial = 0;    
}

//AxisChannelPublisher::~AxisChannelPublisher()
//{    
//}


void AxisChannelPublisher::connect2Bus(ArmBus& oArmBus)
{
    ArmConnector::connect2Bus(oArmBus);        
    // buses for axes
    pBusPan = &oArmBus.getPanBus();
    pBusTilt = &oArmBus.getTiltBus();
    pBusRadial = &oArmBus.getRadialBus();
}

bool AxisChannelPublisher::senseData()
{    
    if (bconnected)
    {
        // read sensed axes positions ...
        axesPositions.pan = pBusPan->getSO_AXIS_POS().getValue();
        axesPositions.tilt = pBusTilt->getSO_AXIS_POS().getValue();
        axesPositions.radial = pBusRadial->getSO_AXIS_POS().getValue();
        // read sensed axes speeds ...
        axesSpeeds.pan = pBusPan->getSO_AXIS_SPEED().getValue();
        axesSpeeds.tilt = pBusTilt->getSO_AXIS_SPEED().getValue();
        axesSpeeds.radial = pBusRadial->getSO_AXIS_SPEED().getValue();        
        return true;
    }
    else
    {
        LOG4CXX_ERROR(logger, "AxisChannelPublisher: can't sense data, not connected to arm bus");
        return false;
    }        
}

bool AxisChannelPublisher::sendData()
{        
    // clear channel
    clearChannel();
    // publish messages with obtained axes data ...
    // positions
    addMessage(AxisTopic::eAXIS_PAN_POS, axesPositions.pan);
    addMessage(AxisTopic::eAXIS_TILT_POS, axesPositions.tilt);
    addMessage(AxisTopic::eAXIS_RAD_POS, axesPositions.radial);
    // speeds
    addMessage(AxisTopic::eAXIS_PAN_SPEED, axesSpeeds.pan);
    addMessage(AxisTopic::eAXIS_TILT_SPEED, axesSpeeds.tilt);
    addMessage(AxisTopic::eAXIS_RAD_SPEED, axesSpeeds.radial);
    publishAll();
    return true;
}

}
