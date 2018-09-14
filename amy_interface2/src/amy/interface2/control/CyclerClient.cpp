/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/control/CyclerClient.h"
#include "amy/interface2/ArmNode.h"
#include "tron/topics/RobotNodes.h"
#include "tron/topics/Topic.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr CyclerClient::logger(Logger::getLogger("amy.interface.control"));

CyclerClient::CyclerClient()
{    
    btuned = false;
    targetCycler = 0;
    clientName = "CyclerClient";
    
    pFreq1Channel = 0;
    pAmp1Channel = 0;
    pAngle1Channel = 0;
    pPhase1Channel = 0;
    pFreq2Channel = 0;
    pAmp2Channel = 0;
    pAngle2Channel = 0;
    pPhase2Channel = 0;
    pRunChannel = 0;
}

//CyclerClient::~CyclerClient()
//{    
//}

bool CyclerClient::tune2Cycler(int i)
{
    if (i < 1 || i > 2)
    {
        LOG4CXX_WARN(logger, clientName + ": invalid target, must be tuned to cycler 1 or 2");
        return false;
    }
    
    targetCycler = i;
    clientName += std::to_string(targetCycler);
    // set topics for arm cycler control
    int node = tron::RobotNodes::eNODE_ARM;
    int section = (targetCycler == 1) ? ArmNode2::eSECTION_CYCLER1 : ArmNode2::eSECTION_CYCLER2;
    int type = tron::Topic::eTYPE_CONTROL;
    
    tron::Topic oTopic;
    ArmNode2 oArmNode;
    // for each channel in section
    for (int channel=0; channel<ArmNode2::eCYCLER_DIM; channel++)
    {
        // set its topic 
        oTopic.set(node, section, channel, type);
        // and add a channel writer for it
        if (oArmNode.buildTopicName(oTopic))
            oComsSender.addChannel(oTopic.getTopicName());            
    }
    
    // store channel pointers for faster access
    pFreq1Channel = oComsSender.getChannel(ArmNode2::eCYCLER_MAIN_FREQ);
    pAmp1Channel = oComsSender.getChannel(ArmNode2::eCYCLER_MAIN_AMP);
    pAngle1Channel = oComsSender.getChannel(ArmNode2::eCYCLER_MAIN_ANGLE);
    pPhase1Channel = oComsSender.getChannel(ArmNode2::eCYCLER_MAIN_PHASE);
    
    pFreq2Channel = oComsSender.getChannel(ArmNode2::eCYCLER_SEC_FREQ);
    pAmp2Channel = oComsSender.getChannel(ArmNode2::eCYCLER_SEC_AMP);
    pAngle2Channel = oComsSender.getChannel(ArmNode2::eCYCLER_SEC_ANGLE);
    pPhase2Channel = oComsSender.getChannel(ArmNode2::eCYCLER_SEC_PHASE);
    
    pRunChannel = oComsSender.getChannel(ArmNode2::eCYCLER_ACTION);        
    
    btuned = true;

    return true;
}

bool CyclerClient::setMainFreq(float value)
{    
    if (!btuned)
        return false;
    LOG4CXX_DEBUG(logger, clientName + ": set main freq > " << std::to_string(value));
    return pFreq1Channel->sendMessage(std::to_string(value));
}

bool CyclerClient::setMainAmplitude(float value)
{    
    if (!btuned)
        return false;
    LOG4CXX_DEBUG(logger, clientName + ": set main amplitude > " << std::to_string(value));
    return pAmp1Channel->sendMessage(std::to_string(value));
}

bool CyclerClient::setMainAngle(float value)
{    
    if (!btuned)
        return false;
    LOG4CXX_DEBUG(logger, clientName + ": set main angle > " << std::to_string(value));
    return pAngle1Channel->sendMessage(std::to_string(value));
}

bool CyclerClient::setMainPhase(float value)
{    
    if (!btuned)
        return false;
    LOG4CXX_DEBUG(logger, clientName + ": set main phase > " << std::to_string(value));
    return pPhase1Channel->sendMessage(std::to_string(value));
}

bool CyclerClient::setSecondaryFreq(float value)
{    
    if (!btuned)
        return false;
    LOG4CXX_DEBUG(logger, clientName + ": set secondary freq > " << std::to_string(value));
    return pFreq2Channel->sendMessage(std::to_string(value));
}

bool CyclerClient::setSecondaryAmplitude(float value)
{    
    if (!btuned)
        return false;
    LOG4CXX_DEBUG(logger, clientName + ": set secondary amplitude > " << std::to_string(value));
    return pAmp2Channel->sendMessage(std::to_string(value));
}

bool CyclerClient::setSecondaryAngle(float value)
{    
    if (!btuned)
        return false;
    LOG4CXX_DEBUG(logger, clientName + ": set secondary angle > " << std::to_string(value));
    return pAngle2Channel->sendMessage(std::to_string(value));
}

bool CyclerClient::setSecondaryPhase(float value)
{    
    if (!btuned)
        return false;
    LOG4CXX_DEBUG(logger, clientName + ": set secondary phase > " << std::to_string(value));
    return pPhase2Channel->sendMessage(std::to_string(value));
}

bool CyclerClient::run(bool bvalue)
{    
    if (!btuned)
        return false;
    LOG4CXX_DEBUG(logger, clientName + ": action > " << std::to_string(bvalue));
    return pRunChannel->sendMessage(std::to_string(bvalue));
}

}