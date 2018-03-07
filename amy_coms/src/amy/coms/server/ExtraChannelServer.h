#ifndef __AMY_COMS_EXTRA_CHANNELSERVER_H
#define __AMY_COMS_EXTRA_CHANNELSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron/talky2/channel/ChannelServer.h"
#include "amy/coms/ArmConnector.h"

namespace amy
{
// Channel server implementation for arm extra topic.
class ExtraChannelServer : public tron::ChannelServer, public ArmConnector
{       
private:
    bool bEndRequested;         // end of arm process requested
    
public:
    ExtraChannelServer();
    //~ExtraChannelServer();
    
    // process commands from received messages
    virtual void processCommands();
    
    bool getArmEndRequested() {return bEndRequested;};
};

}
#endif
