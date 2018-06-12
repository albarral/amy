/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface/channels/ChannelSubscriber4Axes.h"
#include "amy/interface/ArmNode.h"
#include "amy/interface/topics/AxisTopic.h"
#include "tron2/robot/RobotSystem.h"

using namespace log4cxx;

namespace amy
{
ChannelSubscriber4Axes::ChannelSubscriber4Axes()
{    
    int channel = ArmNode::eARM_AXES_CHANNEL;    
    tron2::ChannelSubscriber::connect2Channel(tron2::RobotSystem::eNODE_ARM, channel, ArmNode::getTopic4Channel(channel));
}

void ChannelSubscriber4Axes::processData()
{    
    int code;
    float value;
    
    if (btuned)    
    {        
        // process received messages
        for (std::string message : listMessages)
        {
            LOG4CXX_TRACE(logger, "ChannelSubscriber4Axes: check msg " << message);
            // if message interpreted, inform axes data
            if (oTalker.interpretMessage(message, code, value))
            {
                switch (code)
                {
                    case AxisTopic::eAXIS_PAN_POS:
                        axesPositions.pan = value;
                        break;

                    case AxisTopic::eAXIS_TILT_POS:
                        axesPositions.tilt = value;
                        break;

                    case AxisTopic::eAXIS_RAD_POS:
                        axesPositions.radial = value;
                        break;

                    case AxisTopic::eAXIS_PAN_SPEED:
                        axesSpeeds.pan = value;
                        break;

                    case AxisTopic::eAXIS_TILT_SPEED:
                        axesSpeeds.tilt = value;
                        break;

                    case AxisTopic::eAXIS_RAD_SPEED:
                        axesSpeeds.radial = value;
                        break;
                }    
            }
            else
            {
                LOG4CXX_WARN(logger, "ChannelSubscriber4Axes: axes concept not interpreted");
            }
        }
    }
    else
    {
        LOG4CXX_ERROR(logger, "ChannelSubscriber4Axes: can't process data, communicator not tuned");
        return;
    }        
}

}