#ifndef __AMY_ARM_ARMEXTENDER_H
#define __AMY_ARM_ARMEXTENDER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/arm/modules/AxisDriver3.h"
#include "amy/arm/bus/JointBus.h"
#include "amy/move/ArmTrigonometry.h"

namespace amy
{
// Behaviour used to extend the arm.
// It controls the ELBOW angle to reach a radial target position.
// It's an AxisDriver module.
class ArmExtender: public AxisDriver3
{
private:
        JointBus* pBusVS;   // bus connection to vertical shoulder
        JointBus* pBusEL;   // bus connection to elbow
        float istVS;    // present VS position
        float istEL;    // present EL position
        ArmTrigonometry oArmTrigonometry;
        float istPosPrev;      // previous axis position

    
public:
    ArmExtender();
    //~ArmExtender();
    
    // tunes the module to the real arm sizes (in cm)
    void tune2Arm(int humerusLen, int radiusLen);        
    // senses the initial position
    void senseInitialPosition();                          
    
private:       
    virtual void selectBusJoints();        
    // read bus data
    virtual void senseBus();
    // write action commands to bus
    virtual void writeBus();
    // computes distance to target
    virtual float computeDistance();       
        

};
}
#endif
