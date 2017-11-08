#ifndef __AMY_COMS_AMYLISTENER_H
#define __AMY_COMS_AMYLISTENER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/coms/ComsData.h"
#include "amy/coms/in/AmyComsServer.h"
#include "amy/core/bus/ArmBus.h"
#include "comy/file/ComyFileServer.h"
#include "tuly/control/module2.h"

namespace amy
{
// This module listens to external control request for amy control and processes them.
// It uses a communications server (from libtron_comy) and an amy control server.
class AmyListener : public tuly::Module2
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // logic
    comy::ComyFileServer oComyServerJoints;      // communications server for joint category
    comy::ComyFileServer oComyServerAxis;      // communications server for axis category
    comy::ComyFileServer oComyServerCyclic;      // communications server for cyclic category
    comy::ComyFileServer oComyServerExtra;      // communications server for extra category
    AmyComsServer oAmyComsServer;       // amy control server
    ComsData oComsData;     // shared coms data

public:
    AmyListener();
    //~AmyListener();

    void init(ArmBus& oArmBus);       
    bool isEnabled() {return benabled;};
        
    // check if there are special actions pending to process
    bool checkSpecialActions();
    // get special actions
    ComsData& getComsData() {return oComsData;};
    // clear special actions
    void clearSpecialActions();    
    
private:
    virtual void first();
    // executes the behaviour
    virtual void loop();
};
}		
#endif
