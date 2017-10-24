#ifndef _AMY_MAIN_AMYBROADCASTER_H
#define _AMY_MAIN_AMYBROADCASTER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "tuly/control/module2.h"
#include "amy/core/ifaces/iArmInterface.h"
#include "amy/coms/AmyComsInformer.h"
#include "comy/file/ComyFilePublisher.h"

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
    comy::ComyFilePublisher oComyPublisher;      // the info publisher (based in shared file)
    AmyComsInformer oAmyComsInformer;           // amy sensor informer

public:
    AmyBroadcaster ();
    //~AmyBroadcaster();

    void init(iArmInterface* pArmInterface);       
    bool isEnabled() {return benabled;};
                
private:
    void first();
    // executes the behaviour
    void loop ();    
};
}		
#endif
