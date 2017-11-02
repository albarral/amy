#ifndef __AMY_MAIN_AMYLISTENER_H
#define __AMY_MAIN_AMYLISTENER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/core/bus/ArmBus.h"
#include "amy/coms/AmyComsServer.h"
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
    comy::ComyFileServer oComyServer;      // communications server
    AmyComsServer oAmyComsServer;       // amy control server

public:
    AmyListener();
    //~AmyListener();

    void init(ArmBus& oArmBus);       
    bool isEnabled() {return benabled;};
    
    // checks if amy end has been requested
    bool checkAmyEndRequested();   
    
private:
    virtual void first();
    // executes the behaviour
    virtual void loop();
};
}		
#endif
