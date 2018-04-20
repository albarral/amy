/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/publisher/AxisChannelPublisher.h"
#include "tron2/talky/arm/AxisTalker.h"
#include "tron2/robot/RobotNodes.h"
#include "tron2/robot/topics/ArmTopics.h"

using namespace log4cxx;

namespace amy
{
AxisChannelPublisher::AxisChannelPublisher()
{    
    tron2::ChannelPublisher::tune4NodeAndTopic(tron2::RobotNodes::eNODE_ARM, tron2::ArmTopics::eARM_AXIS);
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
    addMessage(tron2::AxisTalker::eAXIS_PAN_POS, axesPositions.pan);
    addMessage(tron2::AxisTalker::eAXIS_TILT_POS, axesPositions.tilt);
    addMessage(tron2::AxisTalker::eAXIS_RAD_POS, axesPositions.radial);
    // speeds
    addMessage(tron2::AxisTalker::eAXIS_PAN_SPEED, axesSpeeds.pan);
    addMessage(tron2::AxisTalker::eAXIS_TILT_SPEED, axesSpeeds.tilt);
    addMessage(tron2::AxisTalker::eAXIS_RAD_SPEED, axesSpeeds.radial);
    publishAll();
    return true;
}

}
