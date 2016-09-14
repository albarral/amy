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
    bool bconnected;        // connected to bus
    ArmBus* pBus;           // access to arm bus
    // int priority;
    
public:
    ArmCommander();

    /*! connects to the arm bus */
    void connect(ArmBus& oArmBus);
    /*! checks if bus is connected */
    bool isConnected() {return bconnected;};
    
    /*! sends given command to the arm bus. Returns true if ok, false otherwise */    
    bool sendCommand(ArmCommand& oArmCommand);
    
private:
    /*! sends command to the ArmManager */    
    bool send2ArmManager(ArmCommand& oArmCommand);
    /*! sends command to ArmMover module */    
    bool send2ArmMover(ArmCommand& oArmCommand);
    /*! sends command to ArmPanner module */    
    bool send2ArmPanner(ArmCommand& oArmCommand);
    /*! sends command to ArmTilter module */    
    bool send2ArmTilter(ArmCommand& oArmCommand);
    /*! sends command to ArmExtender module */    
    bool send2ArmExtender(ArmCommand& oArmCommand);
    /*! sends command to JointMover modules */    
    bool send2JointMover(ArmCommand& oArmCommand);
    /*! sends command to JointControl modules */    
    bool send2JointControl(ArmCommand& oArmCommand);
    
};
}
#endif
