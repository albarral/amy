#ifndef __AMY_ARM_ARMINTERFACE_H
#define __AMY_ARM_ARMINTERFACE_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/core/ifaces/iArmInterface.h"
#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/bus/CyclerBus.h"
#include "amy/arm/bus/AxisBus.h"
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
    // cyclers buses
    CyclerBus* pBusFrontalCycler;
    // axes buses
    AxisBus* pBusPan;
    AxisBus* pBusTilt;
    AxisBus* pBusRadial;
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
    
    // CYCLERS
    // set front frequency (Hz)
    virtual void frontFrequency(float value);
    // set front amplitude (degrees)
    virtual void frontAmplitude(float value);
    // set front angle (degrees)
    virtual void frontAngle(float value);
    // start/stop front cyclic movement
    virtual void frontAction(bool bvalue);

    // AXIS SPEEDS
    // change pan speed
    virtual void panSpeed(float value);
    // change tilt speed
    virtual void tiltSpeed(float value);
    // change radial speed
    virtual void radialSpeed(float value);
    // keep arm tilt
    virtual void keepTilt(int value);
    
    // AXIS POSITIONS
    // change arm pan
    virtual void movePan(float angle);
    // change arm tilt
    virtual void moveTilt(float angle);
    // extend arm
    virtual void extend(float radius);

    // JOINT POSITIONS
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

    // JOINT OUTPUTS    
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
