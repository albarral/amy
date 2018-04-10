#ifndef __AMY_COMS_AXIS_CHANNELPUBLISHER_H
#define __AMY_COMS_AXIS_CHANNELPUBLISHER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/ArmConnector.h"
#include "amy/core/bus/AxisBus.h"
#include "tron2/robot/sensors/ArmSensors.h"
#include "tron2/talky/channel/ChannelPublisher.h"

namespace amy
{
// Channel publisher implementation for arm joints topic.
class AxisChannelPublisher : public tron2::ChannelPublisher, public ArmConnector
{            
private:
    tron2::AxesData axesPositions;
    tron2::AxesData axesSpeeds;
    AxisBus* pBusPan;          // access to pan bus 
    AxisBus* pBusTilt;          // access to tilt bus
    AxisBus* pBusRadial;      // access to radial bus
    
public:
    AxisChannelPublisher();
    //~AxisChannelPublisher();
    
    virtual void connect2Bus(ArmBus& oArmBus);

    // sense data from bus
    bool senseData();
    // send data
    bool sendData();
};

}
#endif
