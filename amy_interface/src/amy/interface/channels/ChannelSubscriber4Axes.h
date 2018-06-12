#ifndef __AMY_INTERFACE_ARM_CHANNELSUBSCRIBER_4AXES_H
#define __AMY_INTERFACE_ARM_CHANNELSUBSCRIBER_4AXES_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface/ArmSensors.h"
#include "tron2/coms/ChannelSubscriber.h"

namespace amy
{
// Specific channel subscriber for arm axes topic.
class ChannelSubscriber4Axes : public tron2::ChannelSubscriber
{    
private:
    AxesData axesPositions;
    AxesData axesSpeeds;
        
public:
    ChannelSubscriber4Axes();
    //~ChannelSubscriber4Axes();

    AxesData& getAxesPositions() {return axesPositions;};
    AxesData& getAxesSpeeds() {return axesSpeeds;};
    
    // process data from received messages
    virtual void processData();
};

}
#endif
