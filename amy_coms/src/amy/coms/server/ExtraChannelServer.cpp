/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/server/ExtraChannelServer.h"
#include "tron/talky2/arm/JointTalker.h"
#include "tron/robot/RobotNodes.h"
#include "tron/robot/topics/ArmTopics.h"

using namespace log4cxx;

namespace amy
{
ExtraChannelServer::ExtraChannelServer() : ChannelServer(tron::RobotNodes::eNODE_ARM, tron::ArmTopics::eARM_EXTRA)
{    
}

//JointListener::~JointListener()
//{    
//}

void ExtraChannelServer::processCommands()
{    
    int code;
    float value;
    
    if (!bconnected)
    {
        LOG4CXX_ERROR(logger, "ExtraChannelServer: can't process data, not connected to arm bus");
        return;        
    }
    
    if (btuned)    
    {        
        // process received messages
        for (std::string message : listMessages)
        {
            LOG4CXX_TRACE(logger, "ExtraChannelServer: check msg " << message);
            // if message interpreted, call proper bus action
            if (pTalker->interpretMessage(message, code, value))
            {
                switch (code)
                {
                    case tron::JointTalker::eJOINT_HS_POS:
                        LOG4CXX_INFO(logger, "> set HS " << value);                        
                        pArmBus->getBusHS().getCO_JOINT_ANGLE().request(value);
                        break;

                    case tron::JointTalker::eJOINT_VS_POS:
                        LOG4CXX_INFO(logger, "> set VS " << value);                        
                        pArmBus->getBusVS().getCO_JOINT_ANGLE().request(value);
                        break;

                    case tron::JointTalker::eJOINT_ELB_POS:
                        LOG4CXX_INFO(logger, "> set ELB " << value);                        
                        pArmBus->getBusEL().getCO_JOINT_ANGLE().request(value);
                        break;

                    case tron::JointTalker::eJOINT_HWRI_POS:
                        LOG4CXX_INFO(logger, "> set HW " << value);                        
                        pArmBus->getBusHW().getCO_JOINT_ANGLE().request(value);
                        break;

                    case tron::JointTalker::eJOINT_VWRI_POS:
                        LOG4CXX_INFO(logger, "> set VW " << value);                        
                        pArmBus->getBusVW().getCO_JOINT_ANGLE().request(value);
                        break;

                    default:
                        LOG4CXX_WARN(logger, "ExtraChannelServer: can't process command, untreated joint concept " << code);                                   
                }    
            }
            else
            {
                LOG4CXX_WARN(logger, "ExtraChannelServer: joint command not interpreted");
            }
        }
    }
    else
    {
        LOG4CXX_ERROR(logger, "ExtraChannelServer: can't process data, communicator not tuned");
        return;
    }        
}

}