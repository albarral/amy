/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/control/CyclerServer.h"
#include "amy/interface2/ArmNode.h"
#include "amy/interface2/channels/CyclerSection.h"
#include "tron/topics/RobotNodes.h"
#include "tron/topics/Topic.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr CyclerServer::logger(Logger::getLogger("amy.interface"));

CyclerServer::CyclerServer()
{    
    btuned = false;
    targetCycler = 0;
    serverName = "CyclerServer";
    
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

//CyclerServer::~CyclerServer()
//{    
//}

bool CyclerServer::tune2Cycler(int i)
{
    if (i < 1 || i > 2)
    {
        LOG4CXX_WARN(logger, serverName + ": invalid target, must be tuned to cycler 1 or 2");
        return false;
    }
    
    targetCycler = i;
    serverName += std::to_string(targetCycler);
    // set topics for arm cycler control
    int node = tron::RobotNodes::eNODE_ARM;
    int section = (targetCycler == 1) ? ArmNode2::eSECTION_CYCLER1 : ArmNode2::eSECTION_CYCLER2;
    int type = tron::Topic::eTYPE_CONTROL;
    
    tron::Topic oTopic;
    ArmNode2 oArmNode;
    // for each channel in section
    for (int channel=0; channel<CyclerSection::eCYCLER_DIM; channel++)
    {
        // set its topic 
        oTopic.set(node, section, channel, type);
        // and add a channel reader for it
        if (oArmNode.buildTopicName(oTopic))
            oComsReceiver.addChannel(oTopic.getTopicName());            
    }
    
    // connect all readers
    oComsReceiver.connect();
    
    // store channel pointers for faster access
    pFreq1Channel = oComsReceiver.getChannel(CyclerSection::eCYCLER_MAIN_FREQ);
    pAmp1Channel = oComsReceiver.getChannel(CyclerSection::eCYCLER_MAIN_AMP);
    pAngle1Channel = oComsReceiver.getChannel(CyclerSection::eCYCLER_MAIN_ANGLE);
    pPhase1Channel = oComsReceiver.getChannel(CyclerSection::eCYCLER_MAIN_PHASE);
    
    pFreq2Channel = oComsReceiver.getChannel(CyclerSection::eCYCLER_SEC_FREQ);
    pAmp2Channel = oComsReceiver.getChannel(CyclerSection::eCYCLER_SEC_AMP);
    pAngle2Channel = oComsReceiver.getChannel(CyclerSection::eCYCLER_SEC_ANGLE);
    pPhase2Channel = oComsReceiver.getChannel(CyclerSection::eCYCLER_SEC_PHASE);
    
    pRunChannel = oComsReceiver.getChannel(CyclerSection::eCYCLER_ACTION);        
    
    btuned = true;
    return true;
}

bool CyclerServer::getMainFreq(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pFreq1Channel->getMessages(listMessages) != 0)
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, serverName + ": get main freq > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool CyclerServer::getMainAmplitude(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pAmp1Channel->getMessages(listMessages))
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, serverName + ": get main amplitude > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool CyclerServer::getMainAngle(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pAngle1Channel->getMessages(listMessages))
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, serverName + ": get main angle > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool CyclerServer::getMainPhase(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pPhase1Channel->getMessages(listMessages))
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, serverName + ": get main phase > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool CyclerServer::getSecondaryFreq(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pFreq2Channel->getMessages(listMessages) != 0)
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, serverName + ": get secondary freq > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool CyclerServer::getSecondaryAmplitude(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pAmp2Channel->getMessages(listMessages))
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, serverName + ": get secondary amplitude > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool CyclerServer::getSecondaryAngle(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pAngle2Channel->getMessages(listMessages))
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, serverName + ": get secondary angle > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool CyclerServer::getSecondaryPhase(float& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pPhase2Channel->getMessages(listMessages))
    {
        value = std::stof(listMessages.back());
        LOG4CXX_DEBUG(logger, serverName + ": get secondary phase > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool CyclerServer::getAction(int& value)
{    
    std::vector<std::string> listMessages; 
    // if messages received, get last
    if (pRunChannel->getMessages(listMessages))
    {
        value = std::stoi(listMessages.back());
        LOG4CXX_DEBUG(logger, serverName + ": get action > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

}