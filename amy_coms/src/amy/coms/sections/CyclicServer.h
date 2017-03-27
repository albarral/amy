#ifndef __AMY_COMS_CYCLICSERVER_H
#define __AMY_COMS_CYCLICSERVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/coms/ifaces/iComsCyclic.h"
#include "amy/coms/data/AmyCommand.h"
#include "amy/core/ifaces/iArmInterface.h"

namespace amy
{
// Class used to serve requests for cyclic movements control.
// Requests are transformed into proper calls to amy control interfaces (ie the ArmInterface)
class CyclicServer : public iComsCyclic
{    
private:
    static log4cxx::LoggerPtr logger;    
    iArmInterface* pArmInterface;   // interface for arm control
        
public:
    CyclicServer();
    void connect2Arm(iArmInterface& oArmInterface);

   // transforms command into proper call to arm interface
    bool processCommand(AmyCommand& oAmyCommand);

private:
   // pan cyclic movements
    virtual void panFrequency(float value);
    virtual void panAmplitude(float value);
    virtual void panTrigger();
    virtual void panStop();
    // tilt cyclic movements
    virtual void tiltFrequency(float value);
    virtual void tiltAmplitude(float value);
    virtual void tiltTrigger();
    virtual void tiltStop();

};
}
#endif
