/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/server/ExtraChannelServer.h"
#include "amy/interface/ArmNode.h"
#include "tron2/robot/RobotSystem.h"
#include "tron2/robot/common/ExtraTopic.h"

using namespace log4cxx;

namespace amy
{
ExtraChannelServer::ExtraChannelServer()
{    
    int channel = ArmNode::eARM_EXTRA_CHANNEL;    
    tron2::ChannelServer::connect2Channel(tron2::RobotSystem::eNODE_ARM, channel, ArmNode::getTopic4Channel(channel));    
    bEndRequested = false;
}

//ExtraChannelServer::~ExtraChannelServer()
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
            if (oTalker.interpretMessage(message, code, value))
            {
                switch (code)
                {
                    case tron2::ExtraTopic::eEXTRA_STOP:
                        LOG4CXX_INFO(logger, "> arm stop ... TO DO");                        
                        break;

                    case tron2::ExtraTopic::eEXTRA_END:
                        LOG4CXX_INFO(logger, "> end arm");  
                        bEndRequested = true;
                        break;

                    default:
                        LOG4CXX_WARN(logger, "ExtraChannelServer: can't process command, untreated concept " << code);                                   
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
