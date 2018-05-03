/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/server/JointChannelServer.h"
#include "tron2/robot/RobotSystem.h"
#include "tron2/robot/arm/ArmNode.h"
#include "tron2/robot/arm/JointTopic.h"

using namespace log4cxx;

namespace amy
{
JointChannelServer::JointChannelServer()
{    
    tron2::ChannelServer::tune4NodeAndTopic(tron2::RobotSystem::eNODE_ARM, tron2::ArmNode::eARM_JOINT);    
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
            if (pTalker->interpretMessage(message, code, value))
            {
                switch (code)
                {
                    case tron2::JointTopic::eJOINT_HS_POS:
                        LOG4CXX_INFO(logger, "> set HS " << value);                        
                        pArmBus->getBusHS().getCO_JOINT_ANGLE().request(value);
                        break;

                    case tron2::JointTopic::eJOINT_VS_POS:
                        LOG4CXX_INFO(logger, "> set VS " << value);                        
                        pArmBus->getBusVS().getCO_JOINT_ANGLE().request(value);
                        break;

                    case tron2::JointTopic::eJOINT_ELB_POS:
                        LOG4CXX_INFO(logger, "> set ELB " << value);                        
                        pArmBus->getBusEL().getCO_JOINT_ANGLE().request(value);
                        break;

                    case tron2::JointTopic::eJOINT_HWRI_POS:
                        LOG4CXX_INFO(logger, "> set HW " << value);                        
                        pArmBus->getBusHW().getCO_JOINT_ANGLE().request(value);
                        break;

                    case tron2::JointTopic::eJOINT_VWRI_POS:
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
