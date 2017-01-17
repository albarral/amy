#ifndef _AMY_MAIN_AMYBROADCASTER_H
#define _AMY_MAIN_AMYBROADCASTER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "amy/utils/module2.h"
#include "amy/coms/data/ArmData.h"
//#include "amy/coms/file/AmyFilePublisher.h"
#include "amy/core/ifaces/iArmInterface.h"

namespace amy
{
// This module is in charge of publishing the commanded joint angles to be applied to the arm.
class AmyBroadcaster : public Module2
{
private:
    static log4cxx::LoggerPtr logger;
    // logic
    ArmData oArmData;
//    float angles[AMY_MAX_JOINTS];
//    float lastAngles[AMY_MAX_JOINTS];
    int numJoints;

public:
    AmyBroadcaster ();
    ~AmyBroadcaster();

    // module params
    virtual void init(Arm& oArm);

    // bus connection 
    virtual void connect(ArmBus& oBus);
        
    // ask the module to stop
    void stop();
        
private:
    void first();
    // executes the behaviour
    void loop ();    
};
}		
#endif
