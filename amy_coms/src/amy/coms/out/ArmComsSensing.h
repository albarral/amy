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
#include "nety/NetNodePublisher.h"

namespace amy
{
// Class used to fetch arm sensor info.
// Info is returned in the form of talky command blocks (of arm topic).
class ComsArmSensing 
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
    
public:       
    ComsArmSensing();
    void connect2Arm(ArmBus& oArmBus);
    
    // sense joint angles, convert them to talky commands and add them to given publisher
    bool senseJoints(nety::NetNodePublisher& oNetyPublisher);
    // sense axes positions and speeds, convert them to talky commands and add them to given publisher
    bool senseAxes(nety::NetNodePublisher& oNetyPublisher);
};
}
#endif
