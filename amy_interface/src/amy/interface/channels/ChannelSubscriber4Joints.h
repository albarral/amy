#ifndef __AMY_INTERFACE_ARM_CHANNELSUBSCRIBER_4JOINTS_H
#define __AMY_INTERFACE_ARM_CHANNELSUBSCRIBER_4JOINTS_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface/ArmSensors.h"
#include "tron2/coms/ChannelSubscriber.h"

namespace amy
{
// Specific channel subscriber for arm joints topic.
class ChannelSubscriber4Joints : public tron2::ChannelSubscriber
{    
private:
    JointsData jointPositions;
        
public:
    ChannelSubscriber4Joints();
    //~ChannelSubscriber4Joints();

    JointsData& getJointPositions() {return jointPositions;};
    
    // process data from received messages
    virtual void processData();
};

}
#endif
