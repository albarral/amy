#ifndef __AMY_COMS_CYCLIC_CHANNELSERVER_H
#define __AMY_COMS_CYCLIC_CHANNELSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron2/talky/channel/ChannelServer.h"
#include "amy/coms/ArmConnector.h"

namespace amy
{
// Channel server implementation for arm cyclic topic.
class CyclicChannelServer : public tron2::ChannelServer, public ArmConnector
{            
public:
    CyclicChannelServer();
    //~CyclicChannelServer();
    
    // process commands from received messages
    virtual void processCommands();
};

}
#endif
