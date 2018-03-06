#ifndef __AMY_COMS_ARMCONNECTOR_H
#define __AMY_COMS_ARMCONNECTOR_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/core/bus/ArmBus.h"

namespace amy
{
// Base class used to connect to arm bus.
class ArmConnector 
{    
protected:
    ArmBus* pArmBus;      // access to arm bus
    bool bconnected;
    
public:
    ArmConnector();
    //~ArmConnector();
    
    virtual void connect2Bus(ArmBus& oArmBus);
    bool isConnected() {return bconnected;};
};
}
#endif
