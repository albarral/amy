#ifndef __AMY_SERVER_AMYSERVER_H
#define __AMY_SERVER_AMYSERVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/iAmyComs.h"
#include "amy/core/bus/ArmBus.h"
#include "amy/core/bus/JointBus.h"

namespace amy
{
// Base class used to serve requests from external processes to the amy control.
// Implements the iAmyComs interface.
// Attended requests are transformed into proper control signals transmitted through the amy's bus.    
class AmyServer : public iAmyComs
{    
protected:
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pArmBus;          // arm bus
    // joint buses
    JointBus* pBusHS;      // horiz. shoulder bus
    JointBus* pBusVS;       // vert. shoulder bus
    JointBus* pBusEL;       // elbow bus
    JointBus* pBusHW;      // horiz. wrist bus 
    JointBus* pBusVW;       // vert. wrist bus
        
public:
    AmyServer();

   // bus connection 
   void connect(ArmBus* pArmBus);
   bool isConnected() {return bconnected;};
   
    virtual void movePan(float value);
    virtual void moveTilt(float value);
    virtual void moveRadius(float value);
    
    virtual void setPosHS(float value);
    virtual void setPosVS(float value);
    virtual void setPosELB(float value);
    virtual void setPosHW(float value);
    virtual void setPosVW(float value);
    
    virtual void endAmy();
};
}
#endif
