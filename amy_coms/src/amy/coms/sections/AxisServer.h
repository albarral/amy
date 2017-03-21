#ifndef __AMY_COMS_AXISSERVER_H
#define __AMY_COMS_AXISSERVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/coms/ifaces/iComsAxes.h"
#include "amy/coms/data/AmyCommand.h"
#include "amy/core/ifaces/iArmInterface.h"

namespace amy
{
// Class used to serve requests for axes control.
// Requests are transformed into proper calls to amy control interfaces (ie the ArmInterface)
class AxisServer : public iComsAxes
{    
private:
    static log4cxx::LoggerPtr logger;    
    iArmInterface* pArmInterface;   // interface for arm control
        
public:
    AxisServer();
    void connect2Arm(iArmInterface& oArmInterface);

   // transforms command into proper call to arm interface
    bool processCommand(AmyCommand& oAmyCommand);

private:
   // axis speeds        
    virtual void panSpeed(float value);
    virtual void tiltSpeed(float value);
    virtual void radialSpeed(float value);
    // axis positions       
    virtual void movePan(float value);
    virtual void moveTilt(float value);
    virtual void moveRadius(float value);
};
}
#endif
