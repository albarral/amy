#ifndef __AMY_COMS_AXIS_CHANNELPUBLISHER_H
#define __AMY_COMS_AXIS_CHANNELPUBLISHER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/ArmConnector.h"
#include "amy/core/bus/AxisBus.h"
#include "tron/robot/sensors/ArmSensors.h"
#include "tron/talky2/channel/ChannelPublisher.h"

namespace amy
{
// Channel publisher implementation for arm joints topic.
class AxisChannelPublisher : public tron::ChannelPublisher, public ArmConnector
{            
private:
    tron::AxesData axesPositions;
    tron::AxesData axesSpeeds;
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
