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
#include "amy/coms/server/CyclerChannelServer.h"
#include "amy/coms/server/ExtraChannelServer.h"
#include "tron2/coms/ChannelServer.h"
#include "amy/core/bus/ArmBus.h"
#include "tron/control/module2.h"

namespace amy
{
// This module serves external control request for arm control. 
// It uses a dedicated channel server for each communications channel (one for each arm topic).
class ArmServer : public tron::Module2
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // logic
    JointChannelServer oJointChannelServer;       // communications server for joint channel
    AxisChannelServer oAxisChannelServer;     // communications server for axis channel
    CyclerChannelServer oCycler1ChannelServer;   // communications server for cycler1 channel
    //CyclerChannelServer oCycler2ChannelServer;   // communications server for cycler2 channel
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
    bool checkChannelServer(tron2::ChannelServer& oChannelServer);
};
}		
#endif
