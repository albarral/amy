#ifndef __AMY_COMS_AMYLISTENER_H
#define __AMY_COMS_AMYLISTENER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/core/bus/ArmBus.h"
#include "amy/coms/in/ComsInArmControl.h"
#include "nety/NetNodeServer.h"
#include "tuly/control/module2.h"

namespace amy
{
// This module listens to external control request for amy control and processes them.
// It uses nety server nodes for communications.
class AmyListener : public tuly::Module2
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // logic
    nety::NetNodeServer oNetyServerJoints;      // communications server for joint category
    nety::NetNodeServer oNetyServerAxis;      // communications server for axis category
    nety::NetNodeServer oNetyServerCyclic;      // communications server for cyclic category
    nety::NetNodeServer oNetyServerExtra;      // communications server for extra category
    ComsInArmControl oComsArmControl;         // object that gets talky commands and transforms them to bus control values
    bool brequestedAmyEnd;
    bool brequestedGUIShow;
    bool brequestedGUIHide;

public:
    AmyListener();
    //~AmyListener();

    void init(ArmBus& oArmBus);       
    bool isEnabled() {return benabled;};
        
    // check special actions
    bool checkSpecialActions();    
    bool getAmyEndRequested() {return brequestedAmyEnd;};
    bool getGUISHowRequested() {return brequestedGUIShow;};
    bool getGUIHideRequested() {return brequestedGUIHide;};
        
private:
    virtual void first();
    // executes the behaviour
    virtual void loop();
    // check given server for received messages and process them
    void checkServer(nety::NetNodeServer& oNetyServer);
};
}		
#endif
