#ifndef __AMY_COMS_ARMCOMSCONTROL_H
#define __AMY_COMS_ARMCOMSCONTROL_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "amy/core/ifaces/iArmInterface.h"
#include "talky/coms/Command.h"

namespace amy
{
// Class used to process arm control requests.
// Requests are converted to proper arm interface commands.
class ArmComsControl 
{    
private:
    static log4cxx::LoggerPtr logger;    
    iArmInterface* pArmInterface;   // interface for arm control
    bool bamyEndRequested;  // flag indicating amy has to end        
    
public:
    ArmComsControl();
    void connect2Arm(iArmInterface* pArmInterface);

   // transforms command into proper call to arm interface
    bool processCommand(talky::Command& oCommand);

    bool getAmyEndRequested() {return bamyEndRequested;};
    
private:
    // process command of joint category
    bool processJointCommand(talky::Command& oCommand);
    // process command of axis category
    bool processAxisCommand(talky::Command& oCommand);
    // process command of cyclic category
    bool processCyclicCommand(talky::Command& oCommand);
    // process command of extra category
    bool processExtraCommand(talky::Command& oCommand);

    // dummy method for to do commands
    void toDoCommand(float value);
};
}
#endif
