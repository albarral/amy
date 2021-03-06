#ifndef __AMY_ARM_ARMMODULE3_H
#define __AMY_ARM_ARMMODULE3_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <tron/control/module3.h>
#include "amy/core/bus/ArmBus.h"
#include "amy/arm/config/ArmConfig.h"
#include "amy/core/robot/Arm.h"

namespace amy
{
// Base class for arm modules.
// It has bus connection and a copy of the arm's configuration.
// Usage:
// - tune and connect chip    
// - init
// - on (now it works)
// - off    
class ArmModule3 : public tron::Module3
{
protected:
    bool benabled;
    Arm oArm;                                   // copy of used arm structure
    ArmConfig oArmConfig;     // copy of used arm configuration
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pArmBus;     // pointer to bus

public:
    ArmModule3();
    //~ArmModule3();

    // initialize module
    void init(Arm& oArm, ArmConfig& oArmConfig);
    bool isEnabled() {return benabled;};

    // bus connection 
    void connect(ArmBus& oArmBus);
    bool isConnected() {return bconnected;};
    
protected:
    // read bus data   
    virtual void senseBus() = 0;
    // write action commands or sensor info to bus    
    virtual void writeBus() = 0;
    // show module initialization in logs
    virtual void showInitialized() = 0;

};
}		
#endif
