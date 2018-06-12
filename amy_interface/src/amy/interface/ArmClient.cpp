/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface/ArmClient.h"
#include "amy/interface/ArmNode.h"
#include "amy/interface/topics/JointTopic.h"
#include "amy/interface/topics/AxisTopic.h"
#include "amy/interface/topics/CyclicTopic.h"
#include "tron2/robot/RobotSystem.h"
#include "tron2/robot/common/ExtraTopic.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmClient::logger(Logger::getLogger("amy.interface"));

ArmClient::ArmClient()
{    
    int node = tron2::RobotSystem::eNODE_ARM;
    int channel = ArmNode::eARM_JOINTS_CHANNEL;
    oJointChannelClient.connect2Channel(node, channel, ArmNode::getTopic4Channel(channel));
    channel = ArmNode::eARM_AXES_CHANNEL;
    oAxisChannelClient.connect2Channel(node, channel, ArmNode::getTopic4Channel(channel));
    channel = ArmNode::eARM_CYCLER1_CHANNEL;
    oCycler1ChannelClient.connect2Channel(node, channel, ArmNode::getTopic4Channel(channel));
    channel = ArmNode::eARM_CYCLER2_CHANNEL;
    oCycler2ChannelClient.connect2Channel(node, channel, ArmNode::getTopic4Channel(channel));
    channel = ArmNode::eARM_EXTRA_CHANNEL;
    oExtraChannelClient.connect2Channel(node, channel, ArmNode::getTopic4Channel(channel));
}

ArmClient::~ArmClient()
{    
}

// JOINT TOPIC ...

bool ArmClient::setHS(float value)
{    
    LOG4CXX_DEBUG(logger, "ArmClient: set HS > " << std::to_string(value));
    return oJointChannelClient.sendMessage(JointTopic::eJOINT_HS_POS, value);
}

bool ArmClient::setVS(float value)
{    
    LOG4CXX_DEBUG(logger, "ArmClient: set VS > " << std::to_string(value));
    return oJointChannelClient.sendMessage(JointTopic::eJOINT_VS_POS, value);
}

bool ArmClient::setELB(float value)
{    
    LOG4CXX_DEBUG(logger, "ArmClient: set ELB > " << std::to_string(value));
    return oJointChannelClient.sendMessage(JointTopic::eJOINT_ELB_POS, value);
}

bool ArmClient::setHWRI(float value)
{    
    LOG4CXX_DEBUG(logger, "ArmClient: set HWRI > " << std::to_string(value));
    return oJointChannelClient.sendMessage(JointTopic::eJOINT_HWRI_POS, value);
}

bool ArmClient::setVWRI(float value)
{    
    LOG4CXX_DEBUG(logger, "ArmClient: set VWRI > " << std::to_string(value));
    return oJointChannelClient.sendMessage(JointTopic::eJOINT_VWRI_POS, value);
}

// AXIS TOPIC ...

bool ArmClient::setPan(float value)
{    
    LOG4CXX_DEBUG(logger, "ArmClient: set pan > " << std::to_string(value));
     return oAxisChannelClient.sendMessage(AxisTopic::eAXIS_PAN_POS, value);
}

bool ArmClient::setTilt(float value)
{    
    LOG4CXX_DEBUG(logger, "ArmClient: set tilt > " << std::to_string(value));
     return oAxisChannelClient.sendMessage(AxisTopic::eAXIS_TILT_POS, value);
}

bool ArmClient::setRadial(float value)
{    
    LOG4CXX_DEBUG(logger, "ArmClient: set radius > " << std::to_string(value));
     return oAxisChannelClient.sendMessage(AxisTopic::eAXIS_RAD_POS, value);
}

bool ArmClient::setPanSpeed(float value)
{    
    LOG4CXX_DEBUG(logger, "ArmClient: set pan speed > " << std::to_string(value));
     return oAxisChannelClient.sendMessage(AxisTopic::eAXIS_PAN_SPEED, value);
}

bool ArmClient::setTiltSpeed(float value)
{    
    LOG4CXX_DEBUG(logger, "ArmClient: set tilt speed > " << std::to_string(value));
     return oAxisChannelClient.sendMessage(AxisTopic::eAXIS_TILT_SPEED, value);
}

bool ArmClient::setRadialSpeed(float value)
{    
    LOG4CXX_DEBUG(logger, "ArmClient: set radial speed > " << std::to_string(value));
     return oAxisChannelClient.sendMessage(AxisTopic::eAXIS_RAD_SPEED, value);
}

bool ArmClient::keepTilt()
{
    LOG4CXX_DEBUG(logger, "ArmClient: keep tilt > ");     
    return oAxisChannelClient.sendMessage(AxisTopic::eAXIS_KEEP_TILT, 0.0);        
}

// CYCLIC1 TOPIC ...

bool ArmClient::setCycler1MainAmp(float value)
{
    LOG4CXX_DEBUG(logger, "ArmClient: set cycler1 amp1 > " << std::to_string(value));     
    return oCycler1ChannelClient.sendMessage(CyclicTopic::eCYCLIC_MAIN_AMP, value);    
}

bool ArmClient::setCycler1MainAngle(float value)
{
    LOG4CXX_DEBUG(logger, "ArmClient: set cycler1 angle1 > " << std::to_string(value));     
    return oCycler1ChannelClient.sendMessage(CyclicTopic::eCYCLIC_MAIN_ANGLE, value);    
}

bool ArmClient::setCycler1MainFreq(float value)
{
    LOG4CXX_DEBUG(logger, "ArmClient: set cycler1 freq1 > " << std::to_string(value));     
    return oCycler1ChannelClient.sendMessage(CyclicTopic::eCYCLIC_MAIN_FREQ, value);    
}

bool ArmClient::setCycler1MainPhase(float value)
{
    LOG4CXX_DEBUG(logger, "ArmClient: set cycler1 phase1 > " << std::to_string(value));     
    return oCycler1ChannelClient.sendMessage(CyclicTopic::eCYCLIC_MAIN_PHASE, value);    
}

bool ArmClient::setCycler1SecAmp(float value)
{
    LOG4CXX_DEBUG(logger, "ArmClient: set cycler1 amp2 > " << std::to_string(value));     
    return oCycler1ChannelClient.sendMessage(CyclicTopic::eCYCLIC_SEC_AMP, value);    
}

bool ArmClient::setCycler1SecAngle(float value)
{
    LOG4CXX_DEBUG(logger, "ArmClient: set cycler1 angle2 > " << std::to_string(value));     
    return oCycler1ChannelClient.sendMessage(CyclicTopic::eCYCLIC_SEC_ANGLE, value);    
}

bool ArmClient::setCycler1SecFreq(float value)
{
    LOG4CXX_DEBUG(logger, "ArmClient: set cycler1 freq2 > " << std::to_string(value));     
    return oCycler1ChannelClient.sendMessage(CyclicTopic::eCYCLIC_SEC_FREQ, value);    
}

bool ArmClient::setCycler1SecPhase(float value)
{
    LOG4CXX_DEBUG(logger, "ArmClient: set cycler1 phase2 > " << std::to_string(value));     
    return oCycler1ChannelClient.sendMessage(CyclicTopic::eCYCLIC_SEC_PHASE, value);    
}

bool ArmClient::setCycler1Action(int value)
{
    LOG4CXX_DEBUG(logger, "ArmClient: cycler1 action > " << std::to_string(value));     
    return oCycler1ChannelClient.sendMessage(CyclicTopic::eCYCLIC_ACTION, (float)value);        
}

// CYCLIC2 TOPIC ...

bool ArmClient::setCycler2MainAmp(float value)
{
    LOG4CXX_DEBUG(logger, "ArmClient: set cycler2 amp1 > " << std::to_string(value));     
    return oCycler2ChannelClient.sendMessage(CyclicTopic::eCYCLIC_MAIN_AMP, value);    
}

bool ArmClient::setCycler2MainAngle(float value)
{
    LOG4CXX_DEBUG(logger, "ArmClient: set cycler2 angle1 > " << std::to_string(value));     
    return oCycler2ChannelClient.sendMessage(CyclicTopic::eCYCLIC_MAIN_ANGLE, value);    
}

bool ArmClient::setCycler2MainFreq(float value)
{
    LOG4CXX_DEBUG(logger, "ArmClient: set cycler2 freq1 > " << std::to_string(value));     
    return oCycler2ChannelClient.sendMessage(CyclicTopic::eCYCLIC_MAIN_FREQ, value);    
}

bool ArmClient::setCycler2MainPhase(float value)
{
    LOG4CXX_DEBUG(logger, "ArmClient: set cycler2 phase1 > " << std::to_string(value));     
    return oCycler2ChannelClient.sendMessage(CyclicTopic::eCYCLIC_MAIN_PHASE, value);    
}

bool ArmClient::setCycler2SecAmp(float value)
{
    LOG4CXX_DEBUG(logger, "ArmClient: set cycler2 amp2 > " << std::to_string(value));     
    return oCycler2ChannelClient.sendMessage(CyclicTopic::eCYCLIC_SEC_AMP, value);    
}

bool ArmClient::setCycler2SecAngle(float value)
{
    LOG4CXX_DEBUG(logger, "ArmClient: set cycler2 angle2 > " << std::to_string(value));     
    return oCycler2ChannelClient.sendMessage(CyclicTopic::eCYCLIC_SEC_ANGLE, value);    
}

bool ArmClient::setCycler2SecFreq(float value)
{
    LOG4CXX_DEBUG(logger, "ArmClient: set cycler2 freq2 > " << std::to_string(value));     
    return oCycler2ChannelClient.sendMessage(CyclicTopic::eCYCLIC_SEC_FREQ, value);    
}

bool ArmClient::setCycler2SecPhase(float value)
{
    LOG4CXX_DEBUG(logger, "ArmClient: set cycler2 phase2 > " << std::to_string(value));     
    return oCycler2ChannelClient.sendMessage(CyclicTopic::eCYCLIC_SEC_PHASE, value);    
}

bool ArmClient::setCycler2Action(int value)
{
    LOG4CXX_DEBUG(logger, "ArmClient: cycler2 action > " << std::to_string(value));     
    return oCycler2ChannelClient.sendMessage(CyclicTopic::eCYCLIC_ACTION, (float)value);        
}

// EXTRA TOPIC ...

bool ArmClient::fullStop()
{
    LOG4CXX_DEBUG(logger, "ArmClient: full stop > ");     
    return oExtraChannelClient.sendMessage(tron2::ExtraTopic::eEXTRA_STOP, 0.0);        
}

bool ArmClient::endNode()
{
    LOG4CXX_DEBUG(logger, "ArmClient: end arm > ");     
    return oExtraChannelClient.sendMessage(tron2::ExtraTopic::eEXTRA_END, 0.0);        
}
}