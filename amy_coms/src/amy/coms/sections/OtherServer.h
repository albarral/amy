#ifndef __AMY_COMS_OTHERSERVER_H
#define __AMY_COMS_OTHERSERVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/coms/ifaces/iComsOthers.h"
#include "amy/core/ifaces/iArmInterface.h"
#include "talky/coms/Command.h"

namespace amy
{
// Class used to serve requests for other amy controls.
// Requests are transformed into proper calls to amy control interfaces (ie the ArmInterface)
class OtherServer : public iComsOthers
{    
private:
    static log4cxx::LoggerPtr logger;    
    iArmInterface* pArmInterface;   // interface for arm control
    bool bamyEndRequested;  // flag indicating amy has to end
        
public:
    OtherServer();
    void connect2Arm(iArmInterface& oArmInterface);

   // transforms command into proper call to arm interface
    bool processCommand(talky::Command& oCommand);
    
    bool getAmyEndRequested() {return bamyEndRequested;};

private:
    // keep arm tilt
    virtual void keepTilt(int value);    
    // end amy process
    virtual void endAmy();
    // dummy method for to do commands
    void toDoCommand(float value);

};
}
#endif
