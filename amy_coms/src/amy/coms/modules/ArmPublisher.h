#ifndef _AMY_COMS_ARMPUBLISHER_H
#define _AMY_COMS_ARMPUBLISHER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/core/bus/ArmBus.h"
#include "amy/core/bus/JointBus.h"
#include "amy/interface2/sense/JointsInformer.h"
//#include "amy/coms/publisher/AxisChannelPublisher.h"
#include "tron/control/module2.h"

namespace amy
{
// This module is in charge of publishing the commanded joint angles to be applied to the arm.
// It uses an AmyPublisher object to broadcast the data.
class ArmPublisher : public tron::Module2
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // logic
    JointsInformer oJointsInformer;
//    AxisChannelPublisher oAxisChannelPublisher;       // communications publisher for axis channel
    JointBus* pBusHS;     // access to arm's HS joint
    JointBus* pBusVS;     // access to arm's VS joint
    JointBus* pBusEL;     // access to arm's ELB joint
    JointBus* pBusHW;     // access to arm's HWRI joint
    JointBus* pBusVW;     // access to arm's VWRI joint

public:
    ArmPublisher ();
    //~ArmPublisher();

    void init(ArmBus& oArmBus);       
    bool isEnabled() {return benabled;};
                
private:
    void first();
    // executes the behaviour
    void loop ();    
    
    void publishJointsSection();        
    
};
}		
#endif
