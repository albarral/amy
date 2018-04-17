/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/publisher/JointChannelPublisher.h"
#include "tron2/talky/arm/JointTalker.h"
#include "tron2/robot/RobotNodes.h"
#include "tron2/robot/topics/ArmTopics.h"

using namespace log4cxx;

namespace amy
{
JointChannelPublisher::JointChannelPublisher() : ChannelPublisher(tron2::RobotNodes::eNODE_ARM, tron2::ArmTopics::eARM_JOINT)
{    
    pBusHS = 0;
    pBusVS = 0;
    pBusEL = 0;
    pBusHW = 0;
    pBusVW = 0;
}

//JointChannelPublisher::~JointChannelPublisher()
//{    
//}


void JointChannelPublisher::connect2Bus(ArmBus& oArmBus)
{
    ArmConnector::connect2Bus(oArmBus);        
    // buses for joints
    pBusHS = &oArmBus.getBusHS();    
    pBusVS = &oArmBus.getBusVS();    
    pBusEL = &oArmBus.getBusEL();    
    pBusHW = &oArmBus.getBusHW();    
    pBusVW = &oArmBus.getBusVW();        
}

bool JointChannelPublisher::senseData()
{    
    if (bconnected)
    {
        // read commanded control values of all joints ...
        jointsData.hs = pBusHS->getCO_JOINT_ANGLE().getValue();
        jointsData.vs = pBusVS->getCO_JOINT_ANGLE().getValue();
        jointsData.elb = pBusEL->getCO_JOINT_ANGLE().getValue();
        jointsData.hwri = pBusHW->getCO_JOINT_ANGLE().getValue();
        jointsData.vwri = pBusVW->getCO_JOINT_ANGLE().getValue();
        return true;
    }
    else
    {
        LOG4CXX_ERROR(logger, "JointChannelPublisher: can't sense data, not connected to arm bus");
        return false;
    }        
}

bool JointChannelPublisher::sendData()
{        
    // clear channel
    clearChannel();
    // publish messages with obtained joints data
    addMessage(tron2::JointTalker::eJOINT_HS_POS, jointsData.hs);
    addMessage(tron2::JointTalker::eJOINT_VS_POS, jointsData.vs);
    addMessage(tron2::JointTalker::eJOINT_ELB_POS, jointsData.elb);
    addMessage(tron2::JointTalker::eJOINT_HWRI_POS, jointsData.hwri);
    addMessage(tron2::JointTalker::eJOINT_VWRI_POS, jointsData.vwri);
    publishAll();
    return true;
}

}