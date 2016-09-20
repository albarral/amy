#ifndef __AMY_ARMCOMMANDER_H
#define __AMY_ARMCOMMANDER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/coms/ArmCommand.h"
#include "amy/arm/bus/ArmBus.h"

namespace amy
{
/** 
 *  Utility class to write commands to the arm bus.
 */
class ArmCommander
{
private:
    // int priority;
    
public:
    ArmCommander();
    
    /*! sends given command to the arm bus. Returns true if ok, false otherwise */    
    bool sendCommand(ArmBus* pBus, ArmCommand& oArmCommand);
    
private:
    /*! sends command to the ArmManager */    
    bool send2ArmManager(ArmBus* pBus, ArmCommand& oArmCommand);
    /*! sends command to ArmMover module */    
    bool send2ArmMover(ArmBus* pBus, ArmCommand& oArmCommand);
    /*! sends command to ArmPanner module */    
    void send2ArmPanner(ArmBus* pBus, ArmCommand& oArmCommand);
    /*! sends command to ArmTilter module */    
    void send2ArmTilter(ArmBus* pBus, ArmCommand& oArmCommand);
    /*! sends command to ArmExtender module */    
    void send2ArmExtender(ArmBus* pBus, ArmCommand& oArmCommand);
    /*! sends command to JointMover modules */    
    void send2JointMover(ArmBus* pBus, ArmCommand& oArmCommand);
    /*! sends command to JointControl modules */    
    void send2JointControl(ArmBus* pBus, ArmCommand& oArmCommand);
    
};
}
#endif
