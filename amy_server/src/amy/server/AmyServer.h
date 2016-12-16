#ifndef __AMY_SERVER_AMYSERVER_H
#define __AMY_SERVER_AMYSERVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/core/bus/ArmBus.h"
#include "amy/core/bus/JointBus.h"

namespace amy
{
// Base class used to serve requests from external processes to the amy control.
// Attended requests are transformed into proper control signals transmitted through the amy's bus.    
class AmyServer
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
   
protected:
    void movePan(int value);
    void moveTilt(int value);
    void moveRadius(int value);    
    
    void setPosHS(float value);
    void setPosVS(float value);
    void setPosELB(float value);
    void setPosHW(float value);
    void setPosVW(float value);
    
    void endAmy();
};
}
#endif
