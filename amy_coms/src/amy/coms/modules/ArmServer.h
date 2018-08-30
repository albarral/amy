#ifndef __AMY_COMS_ARMSERVER_H
#define __AMY_COMS_ARMSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/core/bus/ArmBus.h"
#include "amy/interface2/control/JointsServer.h"
#include "amy/interface2/control/AxesServer.h"
#include "amy/interface2/control/CyclerServer.h"
#include "tron/control/module2.h"
#include "tron/interface/ExtraServer.h"

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
    ArmBus* pArmBus;      // access to arm bus    
    JointsServer oJointsServer;
    AxesServer oAxesServer;    
    CyclerServer oCyclerServer1;
    CyclerServer oCyclerServer2;
    tron::ExtraServer oExtraServer;    // communications server for extra channel
    bool bEndRequested;         // end of arm process requested

public:
    ArmServer();
    //~ArmServer();

    void init(ArmBus& oArmBus);       
    bool isEnabled() {return benabled;};
        
    bool getAmyEndRequested() {return bEndRequested;};        

private:
    virtual void first();
    // executes the behaviour
    virtual void loop();
    
    void checkJointsSection();        
    void checkAxesSection();
    void checkCyclerSection(int i);
    void checkExtraSection();
};
}		
#endif
