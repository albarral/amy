#ifndef _AMY_COMS_AMYBROADCASTER_H
#define _AMY_COMS_AMYBROADCASTER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/core/bus/ArmBus.h"
#include "amy/coms/out/AmyComsInformer.h"
#include "comy/file/ComyFilePublisher.h"
#include "tuly/control/module2.h"

namespace amy
{
// This module is in charge of publishing the commanded joint angles to be applied to the arm.
// It uses an AmyPublisher object to broadcast the data.
class AmyBroadcaster : public tuly::Module2
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // logic
    comy::ComyFilePublisher oComyPublisherJoints;      // communications publisher for joint category
    //comy::ComyFilePublisher oComyPublisherAxis;    // communications publisher for axis category
    AmyComsInformer oAmyComsInformer;           // amy sensor informer

public:
    AmyBroadcaster ();
    //~AmyBroadcaster();

    void init(ArmBus& oArmBus);       
    bool isEnabled() {return benabled;};
                
private:
    void first();
    // executes the behaviour
    void loop ();    
};
}		
#endif
