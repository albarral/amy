#ifndef __AMY_ARM_ARMINTERFACE_H
#define __AMY_ARM_ARMINTERFACE_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/core/ifaces/iArmInterface.h"
#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/bus/JointBus.h"

namespace amy
{
// Class used to control the arm with a set of predefined requests. To be used by external threads.
// Implements the iArmInterface interface.
// Requests are transformed into proper control signals to the arm's bus.    
class ArmInterface : public iArmInterface
{    
protected:
    // bus
    bool benabled;        // connected to bus
    ArmBus* pArmBus;          // arm bus
    // joint buses
    JointBus* pBusHS;      // horiz. shoulder bus
    JointBus* pBusVS;       // vert. shoulder bus
    JointBus* pBusEL;       // elbow bus
    JointBus* pBusHW;      // horiz. wrist bus 
    JointBus* pBusVW;       // vert. wrist bus
        
public:
    ArmInterface();

    bool isEnabled() {return benabled;};
    // bus connection 
    void connect(ArmBus& oArmBus);
   
    // HIGH LEVEL CONTROL
    // change arm pan
    virtual void movePan(float angle);
    // change arm tilt
    virtual void moveTilt(float angle);
    // extend arm
    virtual void extend(float radius);

    // LOW LEVEL CONTROL
    // set HS position
    virtual void moveHS(float angle);
    // set VS position
    virtual void moveVS(float angle);
    // set EL position
    virtual void moveEL(float angle);
    // set HW position
    virtual void moveHW(float angle);
    // set VW position
    virtual void moveVW(float angle);

    // LOW LEVEL OUTPUTS
    // get HS control angle
    virtual float getHSControl();
    // get VS control angle
    virtual float getVSControl();
    // get EL control angle
    virtual float getELControl();
    // get HW control angle
    virtual float getHWControl();
    // get VW control angle
    virtual float getVWControl();

};
}
#endif
