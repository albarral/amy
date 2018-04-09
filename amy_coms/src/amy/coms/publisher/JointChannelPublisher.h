#ifndef __AMY_COMS_JOINT_CHANNELPUBLISHER_H
#define __AMY_COMS_JOINT_CHANNELPUBLISHER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/ArmConnector.h"
#include "amy/core/bus/JointBus.h"
#include "tron2/robot/sensors/ArmSensors.h"
#include "tron2/talky/channel/ChannelPublisher.h"

namespace amy
{
// Channel publisher implementation for arm joints topic.
class JointChannelPublisher : public tron2::ChannelPublisher, public ArmConnector
{            
private:
    tron2::JointsData jointsData;
    JointBus* pBusHS;     // access to arm's HS joint
    JointBus* pBusVS;     // access to arm's VS joint
    JointBus* pBusEL;     // access to arm's ELB joint
    JointBus* pBusHW;     // access to arm's HWRI joint
    JointBus* pBusVW;     // access to arm's VWRI joint
    
public:
    JointChannelPublisher();
    //~JointChannelPublisher();
    
    virtual void connect2Bus(ArmBus& oArmBus);

    // sense data from bus
    bool senseData();
    // send data
    bool sendData();
};

}
#endif
