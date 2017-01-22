#ifndef __AMY_MAIN_AMYLISTENER_H
#define __AMY_MAIN_AMYLISTENER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/utils/module2.h"
//#include "amy/coms/file/AmyFileServer.h"
#include "amy/coms/zero/AmyZeroMQServer.h"
#include "amy/core/ifaces/iArmInterface.h"

namespace amy
{
// This module listens to external control request for amy control and processes them.
// It uses an AmyServer (file based one) connected to amy's control interfaces..
class AmyListener : public Module2
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
   // logic
    //AmyFileServer oAmyFileServer;     // amy server (using file coms)
    AmyZeroMQServer oAmyZeroMQServer;   //amy zeromq server
    
public:
    AmyListener();
    //~AmyListener();

    void init(iArmInterface& oArmInterface);       
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
