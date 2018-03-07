/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/server/ExtraChannelServer.h"
#include "tron/talky2/arm/BasicTalker.h"
#include "tron/robot/RobotNodes.h"
#include "tron/robot/topics/ArmTopics.h"

using namespace log4cxx;

namespace amy
{
ExtraChannelServer::ExtraChannelServer() : ChannelServer(tron::RobotNodes::eNODE_ARM, tron::ArmTopics::eARM_EXTRA)
{    
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
            if (pTalker->interpretMessage(message, code, value))
            {
                switch (code)
                {
                    case tron::BasicTalker::eEXTRA_ARM_STOP:
                        LOG4CXX_INFO(logger, "> arm stop ... TO DO");                        
                        break;

                    case tron::BasicTalker::eEXTRA_ARM_END:
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
