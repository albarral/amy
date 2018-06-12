#ifndef __AMY_INTERFACE_ARMLISTENER_H
#define __AMY_INTERFACE_ARMLISTENER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "amy/interface/channels/ChannelSubscriber4Joints.h"
#include "amy/interface/channels/ChannelSubscriber4Axes.h"
#include "amy/interface/ArmSensors.h"
#include "tron2/coms/ChannelSubscriber.h"

namespace amy
{
// Arm client class (implementing TronArmListener interface) to sense a robot arm.
class ArmListener
{    
private:
    static log4cxx::LoggerPtr logger;
    ChannelSubscriber4Joints oChannelSubscriber4Joints;
    ChannelSubscriber4Axes oChannelSubscriber4Axes;    
        
public:
    ArmListener();
    //~ArmListener();

    // senses subscribed channels
    bool senseChannels();
    
    // joint topic ...
    // sense joints positions 
    virtual JointsData& getJointPositions();
    // sense joint states
//    virtual JointsData& getJointStates();
//
    // axis topic ...
    // sense axes positions 
    virtual AxesData& getAxesPositions();
    // sense axes speeds 
    virtual AxesData& getAxesSpeeds();
    
private:
    // hear and process info in given channel 
    bool senseChannel(tron2::ChannelSubscriber& oChannelSubscriber);
};

}
#endif
