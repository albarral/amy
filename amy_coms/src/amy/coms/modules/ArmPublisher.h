#ifndef _AMY_COMS_ARMPUBLISHER_H
#define _AMY_COMS_ARMPUBLISHER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/core/bus/ArmBus.h"
#include "amy/coms/publisher/JointChannelPublisher.h"
#include "amy/coms/publisher/AxisChannelPublisher.h"
#include "tuly/control/module2.h"

namespace amy
{
// This module is in charge of publishing the commanded joint angles to be applied to the arm.
// It uses an AmyPublisher object to broadcast the data.
class ArmPublisher : public tuly::Module2
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // logic
    JointChannelPublisher oJointChannelPublisher;      // communications publisher for joints channel
    AxisChannelPublisher oAxisChannelPublisher;       // communications publisher for axis channel

public:
    ArmPublisher ();
    //~ArmPublisher();

    void init(ArmBus& oArmBus);       
    bool isEnabled() {return benabled;};
                
private:
    void first();
    // executes the behaviour
    void loop ();    
};
}		
#endif
