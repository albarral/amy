#ifndef __AMY_COMS_AMYSERVER_H
#define __AMY_COMS_AMYSERVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/iAmyComs.h"
#include "amy/core/ifaces/iArmInterface.h"

namespace amy
{
// Base class used to serve requests from external processes.
// Implements the iAmyComs interface.
// Requests are transformed into proper calls to amy control interfaces (ie the ArmInterface)
class AmyServer : public iAmyComs
{    
protected:
    bool bconnected;        // connected to amy control interfaces
    iArmInterface* pArmInterface;   // interface for arm control
    bool bamyEndRequested;  // flag indicating amy has to end
        
public:
    AmyServer();

   bool isConnected() {return bconnected;};
   void connect2Arm(iArmInterface& oArmInterface);
   
    virtual void movePan(float value);
    virtual void moveTilt(float value);
    virtual void moveRadius(float value);
    
    virtual void setPosHS(float value);
    virtual void setPosVS(float value);
    virtual void setPosELB(float value);
    virtual void setPosHW(float value);
    virtual void setPosVW(float value);
    
    virtual void endAmy();
    bool isAmyEndRequested() {return bamyEndRequested;};
};
}
#endif
