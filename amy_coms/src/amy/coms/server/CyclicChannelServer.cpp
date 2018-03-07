/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/server/CyclicChannelServer.h"
#include "tron/talky2/arm/CyclicTalker.h"
#include "tron/robot/RobotNodes.h"
#include "tron/robot/topics/ArmTopics.h"

using namespace log4cxx;

namespace amy
{
CyclicChannelServer::CyclicChannelServer() : ChannelServer(tron::RobotNodes::eNODE_ARM, tron::ArmTopics::eARM_CYCLIC)
{    
}

//CyclicChannelServer::~CyclicChannelServer()
//{    
//}

void CyclicChannelServer::processCommands()
{    
    int code;
    float value;
    
    if (!bconnected)
    {
        LOG4CXX_ERROR(logger, "CyclicChannelServer: can't process data, not connected to arm bus");
        return;        
    }
    
    if (btuned)    
    {        
        // process received messages
        for (std::string message : listMessages)
        {
            LOG4CXX_TRACE(logger, "CyclicChannelServer: check msg " << message);
            // if message interpreted, call proper bus action
            if (pTalker->interpretMessage(message, code, value))
            {
                switch (code)
                {
                    // FRONTAL CYCLER
                    case tron::CyclicTalker::eCYCLIC_FRONT1_FREQ:
                        LOG4CXX_INFO(logger, "> set front1 freq " << value);                        
                        pArmBus->getFrontalCyclerBus().getCO_CYCLER_FREQ1().request(value);
                        break;

                    case tron::CyclicTalker::eCYCLIC_FRONT1_AMP:
                        LOG4CXX_INFO(logger, "> set front1 amplitude " << value);                        
                        pArmBus->getFrontalCyclerBus().getCO_CYCLER_AMPLITUDE1().request(value);
                        break;

                    case tron::CyclicTalker::eCYCLIC_FRONT1_ANGLE:
                        LOG4CXX_INFO(logger, "> set front1 angle " << value);                        
                        pArmBus->getFrontalCyclerBus().getCO_CYCLER_ANGLE1().request(value);
                        break;

                    case tron::CyclicTalker::eCYCLIC_FRONT2_FREQ:
                        LOG4CXX_INFO(logger, "> set front2 freq " << value);                        
                        pArmBus->getFrontalCyclerBus().getCO_CYCLER_FREQ2().request(value);
                        break;

                    case tron::CyclicTalker::eCYCLIC_FRONT2_AMP:
                        LOG4CXX_INFO(logger, "> set front2 amplitude " << value);                        
                        pArmBus->getFrontalCyclerBus().getCO_CYCLER_AMPLITUDE2().request(value);
                        break;

                    case tron::CyclicTalker::eCYCLIC_FRONT2_ANGLE:
                        LOG4CXX_INFO(logger, "> set front2 angle " << value);                        
                        pArmBus->getFrontalCyclerBus().getCO_CYCLER_ANGLE2().request(value);
                        break;

                    case tron::CyclicTalker::eCYCLIC_FRONT_PHASE:
                        LOG4CXX_INFO(logger, "> set front phase " << value);                        
                        pArmBus->getFrontalCyclerBus().getCO_CYCLER_PHASE().request((int)value);
                        break;

                    case tron::CyclicTalker::eCYCLIC_FRONT_ACTION:
                    {
                        bool bgo = ((int)value != 0); 
                        LOG4CXX_INFO(logger, "> front action " << bgo);                        
                        pArmBus->getFrontalCyclerBus().getCO_CYCLER_ACTION().request(bgo);
                        break;
                    }

                    default:
                        LOG4CXX_WARN(logger, "CyclicChannelServer: can't process command, untreated concept " << code);                                   
                }    
            }
            else
            {
                LOG4CXX_WARN(logger, "CyclicChannelServer: joint command not interpreted");
            }
        }
    }
    else
    {
        LOG4CXX_ERROR(logger, "CyclicChannelServer: can't process data, communicator not tuned");
        return;
    }        
}

}
