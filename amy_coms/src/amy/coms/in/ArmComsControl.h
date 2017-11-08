#ifndef __AMY_COMS_ARMCOMSCONTROL_H
#define __AMY_COMS_ARMCOMSCONTROL_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "amy/coms/ComsData.h"
#include "amy/core/bus/ArmBus.h"
#include "talky/coms/Command.h"

namespace amy
{
// Class used to process arm control requests.
// Requests are converted to proper arm interface commands.
class ArmComsControl 
{    
private:
    static log4cxx::LoggerPtr logger;            
    ArmBus* pArmBus;      // access to arm bus
    
public:
    ArmComsControl();
    void connect2Arm(ArmBus* pArmBus);

   // transforms command into proper call to arm interface
    bool processCommand(talky::Command& oCommand, ComsData& oComsData);
    
private:
    // process command of joint category
    bool processJointCommand(talky::Command& oCommand);
    // process command of axis category
    bool processAxisCommand(talky::Command& oCommand);
    // process command of cyclic category
    bool processCyclicCommand(talky::Command& oCommand);
    // process command of extra category
    bool processExtraCommand(talky::Command& oCommand, ComsData& oComsData);

    // dummy method for to do commands
    void toDoCommand(float value);
};
}
#endif
