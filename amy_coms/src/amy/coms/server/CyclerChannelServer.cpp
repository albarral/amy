/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/server/CyclerChannelServer.h"
#include "tron2/talky/arm/CyclicTalker.h"
#include "tron2/robot/RobotNodes.h"
#include "tron2/robot/topics/ArmTopics.h"

using namespace log4cxx;

namespace amy
{
CyclerChannelServer::CyclerChannelServer()
{    
    targetCycler = 0;
    pCyclerBus = 0;
}

//CyclicChannelServer::~CyclicChannelServer()
//{    
//}

void CyclerChannelServer::setTargetCycler(int i)
{
    if (i == 1 || i == 2)
    {
        targetCycler = i;
        int topic = (targetCycler == 1) ? tron2::ArmTopics::eARM_CYCLER1 : tron2::ArmTopics::eARM_CYCLER2;
        tron2::ChannelServer::tune4NodeAndTopic(tron2::RobotNodes::eNODE_ARM, topic);        
    }
}

void CyclerChannelServer::connect2Bus(ArmBus& oArmBus)
{
    // accept connection only if target cycler defined
    if (targetCycler != 0)
    {
        ArmConnector::connect2Bus(oArmBus);
        pCyclerBus = (targetCycler == 1) ? &(oArmBus.getCyclerBus1()) : &(oArmBus.getCyclerBus2());
    }
}

void CyclerChannelServer::processCommands()
{    
    int code;
    float value;
    
    if (!bconnected)
    {
        LOG4CXX_ERROR(logger, identity << "-CyclicChannelServer:: can't process data, not connected to arm bus");
        return;        
    }
    
    if (btuned)    
    {        
        // process received messages
        for (std::string message : listMessages)
        {
            LOG4CXX_TRACE(logger, identity << "-CyclicChannelServer: check msg " << message);
            // if message interpreted, call proper bus action
            if (pTalker->interpretMessage(message, code, value))
            {
                switch (code)
                {
                    // FRONTAL CYCLER
                    case tron2::CyclicTalker::eCYCLER_MAIN_FREQ:
                        LOG4CXX_INFO(logger, identity << "> set cycler main freq " << value);                        
                        pCyclerBus->getCO_CYCLER_FREQ1().request(value);
                        break;

                    case tron2::CyclicTalker::eCYCLER_MAIN_AMP:
                        LOG4CXX_INFO(logger, identity << "> set cycler main amplitude " << value);                        
                        pCyclerBus->getCO_CYCLER_AMP1().request(value);
                        break;

                    case tron2::CyclicTalker::eCYCLER_MAIN_ANGLE:
                        LOG4CXX_INFO(logger, identity << "> set cycler main angle " << value);                        
                        pCyclerBus->getCO_CYCLER_ANGLE1().request(value);
                        break;

                    case tron2::CyclicTalker::eCYCLER_MAIN_PHASE:
                        LOG4CXX_INFO(logger, identity << "> set cycler main phase " << value);                        
                        pCyclerBus->getCO_CYCLER_PHASE1().request((int)value);
                        break;

                    case tron2::CyclicTalker::eCYCLER_SEC_FREQ:
                        LOG4CXX_INFO(logger, identity << "> set cycler secondary freq " << value);                        
                        pCyclerBus->getCO_CYCLER_FREQ2().request(value);
                        break;

                    case tron2::CyclicTalker::eCYCLER_SEC_AMP:
                        LOG4CXX_INFO(logger, identity << "> set cycler secondary amplitude " << value);                        
                        pCyclerBus->getCO_CYCLER_AMP2().request(value);
                        break;

                    case tron2::CyclicTalker::eCYCLER_SEC_ANGLE:
                        LOG4CXX_INFO(logger, identity << "> set cycler secondary angle " << value);                        
                        pCyclerBus->getCO_CYCLER_ANGLE2().request(value);
                        break;

                    case tron2::CyclicTalker::eCYCLER_SEC_PHASE:
                        LOG4CXX_INFO(logger, identity << "> set cycler secondary phase " << value);                        
                        pCyclerBus->getCO_CYCLER_PHASE2().request((int)value);
                        break;

                    case tron2::CyclicTalker::eCYCLER_ACTION:
                    {
                        bool bgo = ((int)value != 0); 
                        LOG4CXX_INFO(logger, identity << "> cycler action " << bgo);                        
                        pCyclerBus->getCO_CYCLER_ACTION().request(bgo);
                        break;
                    }

                    default:
                        LOG4CXX_WARN(logger, identity << "-CyclicChannelServer: can't process command, untreated concept " << code);                                   
                }    
            }
            else
            {
                LOG4CXX_WARN(logger, identity << "-CyclicChannelServer: cycler command not interpreted");
            }
        }
    }
    else
    {
        LOG4CXX_ERROR(logger, identity << "-CyclicChannelServer: can't process data, communicator not tuned");
        return;
    }        
}

}
