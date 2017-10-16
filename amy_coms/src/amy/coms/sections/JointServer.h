#ifndef __AMY_COMS_JOINTSERVER_H
#define __AMY_COMS_JOINTSERVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/coms/ifaces/iComsJoints.h"
#include "amy/core/ifaces/iArmInterface.h"
#include "talky/coms/Command.h"

namespace amy
{
// Class used to serve requests for joints control.
// Requests are transformed into proper calls to amy control interfaces
class JointServer : public iComsJoints
{    
private:
    static log4cxx::LoggerPtr logger;    
    iArmInterface* pArmInterface;   // interface for arm control
        
public:
    JointServer();
    void connect2Arm(iArmInterface& oArmInterface);

   // transforms command into proper call to arm interface
    bool processCommand(talky::Command& oCommand);

private:
    // joint positions
    virtual void setPosHS(float value);
    virtual void setPosVS(float value);
    virtual void setPosELB(float value);
    virtual void setPosHW(float value);
    virtual void setPosVW(float value);

};
}
#endif
