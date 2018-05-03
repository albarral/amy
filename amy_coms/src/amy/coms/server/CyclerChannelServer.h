#ifndef __AMY_COMS_CYCLER_CHANNELSERVER_H
#define __AMY_COMS_CYCLER_CHANNELSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron2/coms/ChannelServer.h"
#include "amy/coms/ArmConnector.h"
#include "amy/core/bus/CyclerBus.h"

namespace amy
{
// Channel server implementation for arm cyclic topic.
class CyclerChannelServer : public tron2::ChannelServer, public ArmConnector
{            
private: 
    int targetCycler;
    CyclerBus* pCyclerBus;

public:
    CyclerChannelServer();
    //~CyclicChannelServer();
    
    // sets target cycler
    void setTargetCycler(int i);

    virtual void connect2Bus(ArmBus& oArmBus);

    // process commands from received messages
    virtual void processCommands();
};

}
#endif
