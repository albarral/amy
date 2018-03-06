#ifndef __AMY_COMS_ARMSERVER_H
#define __AMY_COMS_ARMSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "amy/coms/server/JointChannelServer.h"
#include "amy/coms/ArmConnector.h"
#include "tron/talky2/channel/ChannelServer.h"

namespace amy
{
// Arm server class
class ArmServer : public ArmConnector
{    
private:
    static log4cxx::LoggerPtr logger;
    JointChannelServer oJointChannelServer;
        
public:
    ArmServer();
    //~ArmServer();

    virtual void connect2Bus(ArmBus& oArmBus);
    // check server channels
    bool checkChannels();
    
private:     
    bool checkChannelServer(tron::ChannelServer& oChannelServer);
};

}
#endif
