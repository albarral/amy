#ifndef __AMY_COMS_AXIS_CHANNELSERVER_H
#define __AMY_COMS_AXIS_CHANNELSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron/talky2/channel/ChannelServer.h"
#include "amy/coms/ArmConnector.h"

namespace amy
{
// Channel server implementation for arm axis topic.
class AxisChannelServer : public tron::ChannelServer, public ArmConnector
{            
public:
    AxisChannelServer();
    //~AxisChannelServer();
    
    // process commands from received messages
    virtual void processCommands();
};

}
#endif
