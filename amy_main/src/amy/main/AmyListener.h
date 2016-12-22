#ifndef __AMY_MAIN_AMYLISTENER_H
#define __AMY_MAIN_AMYLISTENER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/utils/module2.h"
#include "amy/server/file/AmyFileServer.h"
#include "amy/core/bus/ArmBus.h"

namespace amy
{
// This module allows direct control of the arm from the command line.
// The module continuously listens to the command line interpreting user entered commands.
// Then sends requests to the amy process through a proper amy coms client.
class AmyListener : public Module2
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pArmBus;
   // logic
    AmyFileServer oAmyFileServer;     // amy client   

public:
    AmyListener();
    //~AmyListener();

    void init();       
    bool isEnabled() {return benabled;};
    
    // bus connection 
    virtual void connect(ArmBus* pArmBus);
    bool isConnected() {return bconnected;};
        
private:
    virtual void first();
    // executes the behaviour
    virtual void loop ();
};
}		
#endif
