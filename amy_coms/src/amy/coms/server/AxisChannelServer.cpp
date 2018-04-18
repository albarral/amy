/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/server/AxisChannelServer.h"
#include "tron2/talky/arm/AxisTalker.h"
#include "tron2/robot/RobotNodes.h"
#include "tron2/robot/topics/ArmTopics.h"

using namespace log4cxx;

namespace amy
{
AxisChannelServer::AxisChannelServer() : ChannelServer(tron2::RobotNodes::eNODE_ARM, tron2::ArmTopics::eARM_AXIS)
{    
}

//AxisChannelServer::~AxisChannelServer()
//{    
//}

void AxisChannelServer::processCommands()
{    
    int code;
    float value;
    
    if (!bconnected)
    {
        LOG4CXX_ERROR(logger, "AxisChannelServer: can't process data, not connected to arm bus");
        return;        
    }
    
    if (btuned)    
    {        
        // process received messages
        for (std::string message : listMessages)
        {
            LOG4CXX_TRACE(logger, "AxisChannelServer: check msg " << message);
            // if message interpreted, call proper bus action
            if (pTalker->interpretMessage(message, code, value))
            {
                switch (code)
                {
                    case tron2::AxisTalker::eAXIS_PAN_POS:
                        LOG4CXX_INFO(logger, "> set pan " << value);                        
                        pArmBus->getPanBus().getCO_AXIS_POS().request(value);
                        break;

                    case tron2::AxisTalker::eAXIS_TILT_POS:
                        LOG4CXX_INFO(logger, "> set tilt " << value);                        
                        pArmBus->getTiltBus().getCO_AXIS_POS().request(value);
                        break;

                    case tron2::AxisTalker::eAXIS_RAD_POS:
                        LOG4CXX_INFO(logger, "> set radius " << value);                        
                        pArmBus->getRadialBus().getCO_AXIS_POS().request(value);
                        break;

                    case tron2::AxisTalker::eAXIS_PAN_SPEED:
                        LOG4CXX_INFO(logger, "> pan speed " << value);                        
                        pArmBus->getPanBus().getCO_AXIS_SPEED1().request(value);
                        break;

                    case tron2::AxisTalker::eAXIS_TILT_SPEED:
                        LOG4CXX_INFO(logger, "> tilt speed " << value);                        
                       pArmBus->getTiltBus().getCO_AXIS_SPEED1().request(value);
                        break;

                    case tron2::AxisTalker::eAXIS_RAD_SPEED:
                        LOG4CXX_INFO(logger, "> rad speed " << value);                        
                        pArmBus->getRadialBus().getCO_AXIS_SPEED1().request(value);
                        break;
                        
                    case tron2::AxisTalker::eAXIS_KEEP_TILT:
                        LOG4CXX_INFO(logger, "> keep tilt " << value);                        
                        pArmBus->getCO_KEEP_TILT().request((int)value);
                        break;

                    default:
                        LOG4CXX_WARN(logger, "AxisChannelServer: can't process command, untreated concept " << code);                                   
                }    
            }
            else
            {
                LOG4CXX_WARN(logger, "AxisChannelServer: joint command not interpreted");
            }
        }
    }
    else
    {
        LOG4CXX_ERROR(logger, "AxisChannelServer: can't process data, communicator not tuned");
        return;
    }        
}

}

