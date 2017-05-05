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
    // ARM MOVER
    // launch this movement type
    virtual void launchMove(int value);
    // stop movement
    virtual void stopMove();
    // turn the movement these angle (degrees)
    virtual void turnMove(int value);
    // make movement wider/narrower
    virtual void moveWider(bool value);
    // make movement taller/shorter
    virtual void moveTaller(bool value);
    // make movement faster/slower
    virtual void moveFaster(bool value);
    
    // FRONTAL CYCLER
    virtual void frontFrequency(float value);
    virtual void frontAmplitude(float value);
    virtual void frontAngle(float value);
    virtual void frontStart();
    virtual void frontStop();

};
}
#endif
