/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/server/JointChannelServer.h"
#include "amy/interface/ArmNode.h"
#include "amy/interface/topics/JointTopic.h"
#include "tron2/robot/RobotSystem.h"

using namespace log4cxx;

namespace amy
{
JointChannelServer::JointChannelServer()
{    
    int channel = ArmNode::eARM_JOINTS_CHANNEL;    
    tron2::ChannelServer::connect2Channel(tron2::RobotSystem::eNODE_ARM, channel, ArmNode::getTopic4Channel(channel));    
}

//JointChannelServer::~JointChannelServer()
//{    
//}

void JointChannelServer::processCommands()
{    
    int code;
    float value;
    
    if (!bconnected)
    {
        LOG4CXX_ERROR(logger, "JointChannelServer: can't process data, not connected to arm bus");
        return;        
    }
    
    if (btuned)    
    {        
        // process received messages
        for (std::string message : listMessages)
        {
            LOG4CXX_TRACE(logger, "JointChannelServer: check msg " << message);
            // if message interpreted, call proper bus action
            if (oTalker.interpretMessage(message, code, value))
            {
                switch (code)
                {
                    case JointTopic::eJOINT_HS_POS:
                        LOG4CXX_INFO(logger, "> set HS " << value);                        
                        pArmBus->getBusHS().getCO_JOINT_ANGLE().request(value);
                        break;

                    case JointTopic::eJOINT_VS_POS:
                        LOG4CXX_INFO(logger, "> set VS " << value);                        
                        pArmBus->getBusVS().getCO_JOINT_ANGLE().request(value);
                        break;

                    case JointTopic::eJOINT_ELB_POS:
                        LOG4CXX_INFO(logger, "> set ELB " << value);                        
                        pArmBus->getBusEL().getCO_JOINT_ANGLE().request(value);
                        break;

                    case JointTopic::eJOINT_HWRI_POS:
                        LOG4CXX_INFO(logger, "> set HW " << value);                        
                        pArmBus->getBusHW().getCO_JOINT_ANGLE().request(value);
                        break;

                    case JointTopic::eJOINT_VWRI_POS:
                        LOG4CXX_INFO(logger, "> set VW " << value);                        
                        pArmBus->getBusVW().getCO_JOINT_ANGLE().request(value);
                        break;

                    default:
                        LOG4CXX_WARN(logger, "JointChannelServer: can't process command, untreated concept " << code);                                   
                }    
            }
            else
            {
                LOG4CXX_WARN(logger, "JointChannelServer: joint command not interpreted");
            }
        }
    }
    else
    {
        LOG4CXX_ERROR(logger, "JointChannelServer: can't process data, communicator not tuned");
        return;
    }        
}

}
