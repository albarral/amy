#ifndef __AMY_COMS_ARMSERVER_H
#define __AMY_COMS_ARMSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/core/bus/ArmBus.h"
#include "amy/core/bus/JointBus.h"
#include "amy/core/bus/AxisBus.h"
#include "amy/core/bus/CyclerBus.h"
#include "amy/interface2/control/JointsServer.h"
#include "amy/interface2/control/AxesServer.h"
#include "amy/interface2/control/CyclerServer.h"
#include "tron/control/module2.h"
#include "tron/interface/ExtraServer.h"

namespace amy
{
// This module serves external control requests for arm control. 
// It uses an ignition based server for each arm node's section.
class ArmServer : public tron::Module2
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // bus connections
    AxisBus* pBusPan;          // access to pan bus 
    AxisBus* pBusTilt;          // access to tilt bus
    AxisBus* pBusRadial;      // access to radial bus
    CyclerBus* pCyclerBus1;
    CyclerBus* pCyclerBus2;
    // logic
    ArmBus* pArmBus;      // access to arm bus    
    JointsServer oJointsServer;
    AxesServer oAxesServer;    
    CyclerServer oCyclerServer1;
    CyclerServer oCyclerServer2;
    tron::ExtraServer oExtraServer;      
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
    void checkCyclerSection(CyclerServer& oCyclerServer, CyclerBus* pCyclerBus, std::string identity);
    void checkExtraSection();
};
}		
#endif
