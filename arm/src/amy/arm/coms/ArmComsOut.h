#ifndef __AMY_ARMCOMS_OUT_H
#define __AMY_ARMCOMS_OUT_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "amy/arm/util/ArmModule.h"
#include "amy/network/ArmNetwork.h"
#include "amy/network/ArmData.h"
#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/bus/JointBus.h"
#include "amy/arm/config/ArmDefines.h"

namespace amy
{
// This module is in charge of putting the obtained arm control outputs (commanded joint angles) in the amy's network.
class ArmComsOut : public ArmModule
{
private:
    static log4cxx::LoggerPtr logger;
    // logic
    ArmNetwork oArmNetwork;
    ArmDataN oArmData;
    JointBus* pBusHShoulder;    // access to horizonal shoulder bus
    JointBus* pBusVShoulder;    // access to vertical shoulder bus
    JointBus* pBusElbow;          // access to elbow bus  
    JointBus* pBusVWrist;            // access to wrist bus    
    float angles[AMY_MAX_JOINTS];
    float lastAngles[AMY_MAX_JOINTS];
    int numJoints;

public:
    ArmComsOut ();
    ~ArmComsOut();

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
