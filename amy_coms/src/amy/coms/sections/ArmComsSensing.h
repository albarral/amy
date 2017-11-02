#ifndef __AMY_COMS_ARMCOMSSENSING_H
#define __AMY_COMS_ARMCOMSSENSING_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "amy/core/bus/ArmBus.h"
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
    DataBlockJoints oDataBlockJoints;                      // data block for joint angles
    DataBlockJointDrivers oDataBlockJointDrivers;     // data block for joint states
    DataBlockAxes oDataBlockAxes;                        // data block for axes positions and speeds
    
public:       
    // fetch arm sensor info through the arm interface
    bool fetchArmInfo(ArmBus* pArmBus, talky::CommandBlock& oCommandBlock);
    
private:
    // read commanded joint angles
    bool senseJointAngles(ArmBus* pArmBus, talky::CommandBlock& oCommandBlock);
    // read joint driver states 
    bool senseJointStates(ArmBus* pArmBus, talky::CommandBlock& oCommandBlock);
    // read axes positions and speeds
    bool senseArmAxes(ArmBus* pArmBus, talky::CommandBlock& oCommandBlock);
};
}
#endif
