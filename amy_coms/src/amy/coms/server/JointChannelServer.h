#ifndef __AMY_COMS_JOINT_CHANNELSERVER_H
#define __AMY_COMS_JOINT_CHANNELSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron/talky2/channel/ChannelServer.h"
#include "amy/coms/ArmConnector.h"

namespace amy
{
// Channel server implementation for arm joints topic.
class JointChannelServer : public tron::ChannelServer, public ArmConnector
{            
public:
    JointChannelServer();
    //~JointChannelServer();
    
    // process commands from received messages
    virtual void processCommands();
};

}
#endif
