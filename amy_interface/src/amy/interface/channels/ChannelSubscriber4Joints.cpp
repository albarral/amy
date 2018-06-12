/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface/channels/ChannelSubscriber4Joints.h"
#include "amy/interface/ArmNode.h"
#include "amy/interface/topics/JointTopic.h"
#include "tron2/robot/RobotSystem.h"

using namespace log4cxx;

namespace amy
{
ChannelSubscriber4Joints::ChannelSubscriber4Joints()
{    
    int channel = ArmNode::eARM_JOINTS_CHANNEL;    
    tron2::ChannelSubscriber::connect2Channel(tron2::RobotSystem::eNODE_ARM, channel, ArmNode::getTopic4Channel(channel));
}

void ChannelSubscriber4Joints::processData()
{    
    int code;
    float value;
    
    if (btuned)    
    {        
        // process received messages
        for (std::string message : listMessages)
        {
            LOG4CXX_TRACE(logger, "ChannelSubscriber4Joints: check msg " << message);
            // if message interpreted, inform joints data
            if (oTalker.interpretMessage(message, code, value))
            {
                switch (code)
                {
                    case JointTopic::eJOINT_HS_POS:
                        jointPositions.hs = value;
                        break;

                    case JointTopic::eJOINT_VS_POS:
                        jointPositions.vs = value;
                        break;

                    case JointTopic::eJOINT_ELB_POS:
                        jointPositions.elb = value;
                        break;

                    case JointTopic::eJOINT_HWRI_POS:
                        jointPositions.hwri = value;
                        break;

                    case JointTopic::eJOINT_VWRI_POS:
                        jointPositions.vwri = value;
                        break;
                }    
            }
            else
            {
                LOG4CXX_WARN(logger, "ChannelSubscriber4Joints: joint position not interpreted");
            }
        }
    }
    else
    {
        LOG4CXX_ERROR(logger, "ChannelSubscriber4Joints: can't process data, communicator not tuned");
        return;
    }        
}

}