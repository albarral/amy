#ifndef __AMY_COMS_ARMCOMSSENSING_H
#define __AMY_COMS_ARMCOMSSENSING_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "amy/core/bus/ArmBus.h"
#include "amy/core/bus/AxisBus.h"
#include "amy/core/bus/JointBus.h"
#include "amy/talk/DataBlockAxes.h"
#include "amy/talk/DataBlockJoints.h"
#include "amy/talk/DataBlockJointDrivers.h"
#include "talky/coms/CommandBlock.h"

namespace amy
{
// Class used to fetch arm sensor info.
// Info is returned in the form of talky command blocks (of arm topic).
class ArmComsSensing 
{    
private:
    static log4cxx::LoggerPtr logger;    
    JointBus* pBusHS;     // access to arm's HS joint
    JointBus* pBusVS;     // access to arm's VS joint
    JointBus* pBusEL;     // access to arm's ELB joint
    JointBus* pBusHW;     // access to arm's HWRI joint
    JointBus* pBusVW;     // access to arm's VWRI joint
    AxisBus* pBusPan;          // access to pan bus 
    AxisBus* pBusTilt;          // access to tilt bus
    AxisBus* pBusRadial;      // access to radial bus
    DataBlockJoints oDataBlockJoints;                      // data block for joint angles
    DataBlockJointDrivers oDataBlockJointDrivers;     // data block for joint states
    DataBlockAxes oDataBlockAxes;                        // data block for axes positions and speeds
    
public:       
    ArmComsSensing();
    void connect2Arm(ArmBus& oArmBus);
    
    // read commanded joint angles (and convert it to command block)
    bool senseJointAngles(talky::CommandBlock& oCommandBlock);
    // read joint driver states (and convert it to command block)
    bool senseJointStates(talky::CommandBlock& oCommandBlock);
    // read axes positions and speeds (and convert it to command block)
    bool senseArmAxes(talky::CommandBlock& oCommandBlock);
};
}
#endif
