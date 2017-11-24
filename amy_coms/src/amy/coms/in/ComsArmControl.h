#ifndef __AMY_COMS_COMSARMCONTROL_H
#define __AMY_COMS_COMSARMCONTROL_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "amy/core/bus/ArmBus.h"
#include "talky/coms/Command.h"
#include "tuly/utils/IntegerQueue.h"

namespace amy
{
// Class used to process arm control requests.
// Requests are converted to proper arm interface commands.
class ComsArmControl 
{    
public:
    // special actions
    enum eAction
    {
         eACTION_AMY_END,            // end amy process
         eACTION_SHOW_GUI,          // show gui
         eACTION_HIDE_GUI             // hide gui
    };

private:
    static log4cxx::LoggerPtr logger;            
    ArmBus* pArmBus;      // access to arm bus
    tuly::IntegerQueue oQueueSpecialActions;  // queue of special actions
    
public:
    ComsArmControl();
    //~ComsArmControl();
    
    void connect2Arm(ArmBus* pArmBus);

   // transforms command into proper call to arm interface
    bool processCommand(talky::Command& oCommand);
    
    tuly::IntegerQueue& getQueueSpecialActions() {return oQueueSpecialActions;}
    
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
