#ifndef __AMY_COMS_AMYPUBLISHER_H
#define __AMY_COMS_AMYPUBLISHER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/iAmyPublisher.h"
#include "amy/coms/data/ArmData.h"
#include "amy/core/ifaces/iArmInterface.h"

namespace amy
{
// Base class used to publish amy info to be consumed by external processes.
// Info from amy control is obtained through the amy interface.
class AmyPublisher : public iAmyPublisher
{    
protected:
    bool bconnected;        // connected to amy interface
    iArmInterface* pArmInterface;   // interface for arm control
    ArmData oArmData;       // control data for an arm's joints
        
public:
    AmyPublisher();

   bool isConnected() {return bconnected;};
   void connect2Arm(iArmInterface& oArmInterface);
   
    // publish commanded joint control positions (angles)
    virtual void publishArmControl();
    
private:
   // info publishing method (specific for each AmyPublisher implementation)
    virtual void publishInfo() = 0;
};
}
#endif
