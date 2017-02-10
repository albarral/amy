#ifndef __AMY_ARM_MODULE_H
#define __AMY_ARM_MODULE_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/config/AmyArmConfig.h"
#include "amy/core/robot/Arm.h"
#include <amy/utils/module2.h>

namespace amy
{
// Base class for amy arm modules.
// It's associated to a hierarchical level & holds a connection to the ArmBus.
// usage: set level, init, connect and on
class ArmModule : public Module2
{
private:
    int level;              // module's level (hierarchy level in the control architecture)
protected:
    std::string modName;   // module name
    bool benabled;
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pArmBus;

public:
    ArmModule();
    //~ArmModule();

    void setLevel(int value) {level = value;};
    int getLevel() {return level;};

    virtual void init(Arm& oArm, AmyArmConfig& oAmyArmConfig) = 0;       // abstract method
    bool isEnabled() {return benabled;};

    // bus connection 
    virtual void connect(ArmBus& oArmBus);
    bool isConnected() {return bconnected;};

    std::string getModuleName() {return modName;};
};
}		
#endif
