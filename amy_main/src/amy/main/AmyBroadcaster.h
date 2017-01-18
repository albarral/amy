#ifndef _AMY_MAIN_AMYBROADCASTER_H
#define _AMY_MAIN_AMYBROADCASTER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "amy/utils/module2.h"
#include "amy/coms/file/AmyFilePublisher.h"
#include "amy/coms/data/ArmData.h"
#include "amy/core/ifaces/iArmInterface.h"

namespace amy
{
// This module is in charge of publishing the commanded joint angles to be applied to the arm.
// It uses an AmyPublisher object to broadcast the data.
class AmyBroadcaster : public Module2
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // logic
    AmyFilePublisher oAmyPublisher;          // the info publisher (based in shared file)
    ArmData oArmData;                             // data to be broadcasted
    ArmData oArmData0;                           // data storage (for change detection)
    iArmInterface* pArmInterface;               // interface to the arm's control

public:
    AmyBroadcaster ();
    //~AmyBroadcaster();

    void init(iArmInterface& oArmInterface);       
    bool isEnabled() {return benabled;};
                
private:
    void first();
    // executes the behaviour
    void loop ();    
    // fetch joints control info through the arm's interface
    void fetchInfo();
};
}		
#endif
