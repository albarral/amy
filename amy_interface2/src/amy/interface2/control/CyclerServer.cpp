/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/control/CyclerServer.h"
#include "amy/interface2/ArmNode.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr CyclerServer::logger2(Logger::getLogger("amy.interface.control"));

CyclerServer::CyclerServer()
{    
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
        LOG4CXX_WARN(logger2, serverName + ": invalid target, must be tuned to cycler 1 or 2");
        return false;
    }
    
    targetCycler = i;
    serverName += std::to_string(targetCycler);

    // set proper section
    int section = (targetCycler == 1) ? ArmNode2::eSECTION_CYCLER1 : ArmNode2::eSECTION_CYCLER2;
    
    ArmNode2 oArmNode;
    // set topics for arm cycler control
    tron::SectionServer::tune4Node(oArmNode, section);
    
    if (isTuned())
    {
        // store channel pointers for faster access
        pFreq1Channel = oComsReceiver.getChannel(ArmNode2::eCYCLER_MAIN_FREQ);
        pAmp1Channel = oComsReceiver.getChannel(ArmNode2::eCYCLER_MAIN_AMP);
        pAngle1Channel = oComsReceiver.getChannel(ArmNode2::eCYCLER_MAIN_ANGLE);
        pPhase1Channel = oComsReceiver.getChannel(ArmNode2::eCYCLER_MAIN_PHASE);

        pFreq2Channel = oComsReceiver.getChannel(ArmNode2::eCYCLER_SEC_FREQ);
        pAmp2Channel = oComsReceiver.getChannel(ArmNode2::eCYCLER_SEC_AMP);
        pAngle2Channel = oComsReceiver.getChannel(ArmNode2::eCYCLER_SEC_ANGLE);
        pPhase2Channel = oComsReceiver.getChannel(ArmNode2::eCYCLER_SEC_PHASE);

        pRunChannel = oComsReceiver.getChannel(ArmNode2::eCYCLER_ACTION);        
    }
    
    return btuned;
}

bool CyclerServer::getMainFreq(float& value)
{    
    // if main freq command received, get it
    if (pFreq1Channel->hasNew())
    {
        value = std::stof(pFreq1Channel->getMessage());
        LOG4CXX_DEBUG(logger2, serverName + ": get main freq > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool CyclerServer::getMainAmplitude(float& value)
{    
    // if main amp command received, get it
    if (pAmp1Channel->hasNew())
    {
        value = std::stof(pAmp1Channel->getMessage());
        LOG4CXX_DEBUG(logger2, serverName + ": get main amplitude > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool CyclerServer::getMainAngle(float& value)
{    
    // if main angle command received, get it
    if (pAngle1Channel->hasNew())
    {
        value = std::stof(pAngle1Channel->getMessage());
        LOG4CXX_DEBUG(logger2, serverName + ": get main angle > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool CyclerServer::getMainPhase(float& value)
{    
    // if main phase command received, get it
    if (pPhase1Channel->hasNew())
    {
        value = std::stof(pPhase1Channel->getMessage());
        LOG4CXX_DEBUG(logger2, serverName + ": get main phase > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool CyclerServer::getSecondaryFreq(float& value)
{    
    // if secondary freq command received, get it
    if (pFreq2Channel->hasNew())
    {
        value = std::stof(pFreq2Channel->getMessage());
        LOG4CXX_DEBUG(logger2, serverName + ": get secondary freq > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool CyclerServer::getSecondaryAmplitude(float& value)
{    
    // if secondary amp command received, get it
    if (pAmp2Channel->hasNew())
    {
        value = std::stof(pAmp2Channel->getMessage());
        LOG4CXX_DEBUG(logger2, serverName + ": get secondary amplitude > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool CyclerServer::getSecondaryAngle(float& value)
{    
    // if secondary angle command received, get it
    if (pAngle2Channel->hasNew())
    {
        value = std::stof(pAngle2Channel->getMessage());
        LOG4CXX_DEBUG(logger2, serverName + ": get secondary angle > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool CyclerServer::getSecondaryPhase(float& value)
{    
    // if secondary phase command received, get it
    if (pPhase2Channel->hasNew())
    {
        value = std::stof(pPhase2Channel->getMessage());
        LOG4CXX_DEBUG(logger2, serverName + ": get secondary phase > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool CyclerServer::getAction(int& value)
{    
    // if action command received, get it
    if (pRunChannel->hasNew())
    {
        value = std::stoi(pRunChannel->getMessage());
        LOG4CXX_DEBUG(logger2, serverName + ": get action > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

}