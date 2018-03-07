#ifndef __AMY_COMS_ARMSERVER_H
#define __AMY_COMS_ARMSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>


#include "amy/coms/server/JointChannelServer.h"
#include "amy/coms/server/AxisChannelServer.h"
#include "amy/coms/server/CyclicChannelServer.h"
#include "amy/coms/server/ExtraChannelServer.h"
#include "tron/talky2/channel/ChannelServer.h"
#include "amy/core/bus/ArmBus.h"
#include "tuly/control/module2.h"

namespace amy
{
// This module serves external control request for arm control. 
// It uses a dedicated channel server for each communications channel (one for each arm topic).
class ArmServer : public tuly::Module2
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // logic
    JointChannelServer oJointChannelServer;       // communications server for joint channel
    AxisChannelServer oAxisChannelServer;     // communications server for axis channel
    CyclicChannelServer oCyclicChannelServer;   // communications server for cyclic channel
    ExtraChannelServer oExtraChannelServer;    // communications server for extra channel

public:
    ArmServer();
    //~ArmServer();

    void init(ArmBus& oArmBus);       
    bool isEnabled() {return benabled;};
        
    bool getAmyEndRequested();        

private:
    virtual void first();
    // executes the behaviour
    virtual void loop();
    // check given channel server for received messages and process them
    bool checkChannelServer(tron::ChannelServer& oChannelServer);
};
}		
#endif
