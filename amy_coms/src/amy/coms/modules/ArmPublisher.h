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
#include "amy/core/bus/AxisBus.h"
#include "amy/interface2/sense/JointsInformer.h"
#include "amy/interface2/sense/AxesInformer.h"
#include "tron/control/module2.h"

namespace amy
{
// This module is in charge of publishing updated arm info to be used by other nodes (joint positions, axes positions, axes speeds ...)
// It uses an ignition based informer for each arm node's section.
class ArmPublisher : public tron::Module2
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // logic
    JointsInformer oJointsInformer;
    AxesInformer oAxesInformer;  
    JointBus* pBusHS;     // access to arm's HS joint
    JointBus* pBusVS;     // access to arm's VS joint
    JointBus* pBusEL;     // access to arm's ELB joint
    JointBus* pBusHW;     // access to arm's HWRI joint
    JointBus* pBusVW;     // access to arm's VWRI joint
    AxisBus* pBusPan;          // access to pan bus 
    AxisBus* pBusTilt;          // access to tilt bus
    AxisBus* pBusRadial;      // access to radial bus

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
    void publishAxesSection();        
    
};
}		
#endif
