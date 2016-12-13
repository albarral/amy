#ifndef __AMY_ARM_ARMEXTENDER_H
#define __AMY_ARM_ARMEXTENDER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/arm/modules/ArmDriver.h"
#include "amy/core/bus/JointBus.h"
#include "amy/arm/move/JointDriver.h"
#include "amy/arm/move/RadialDriver.h"

namespace amy
{
// Behaviour used to extend the arm. 
// Performs a dual movement involving coordination of the elbow & the vertical shoulder.
// It senses for arm tilt and radius requests (from bus) and controls the vertical shoulder & elbow angles to reach those values.
// Derived from ArmDriver.
// Controlled joints:
// - VERTICAL SHOULDER (VS)    
// - ELBOW (EL)            
class ArmExtender: public ArmDriver
{
private:
    // bus
    JointBus* pBusVS;   // bus connection to vertical shoulder
    JointBus* pBusEL;   // bus connection to elbow
    // request
    float targetTilt;              // requested arm tilt
    float targetRadius;         // requested arm radius
    // sense
    float istVS;                     // measured vertical shoulder position
    float istElbow;                // measured elbow position
    int vsLimitReached;          // value indicating the vertical shoulder movement is blocked (due to reached joint limit)    
    int elbowLimitReached;     // value indicating the elbow movement is blocked (due to reached joint limit)    
    // control
    float vsAccel;                  // commanded vertical shoulder acceleration 
    float elbowAccel;             // commanded elbow acceleration 
    // logic
    JointDriver oJointDriver;         // utility class to drive the vertical shoulder (VS)
    RadialDriver oRadialDriver;    // utility class to drive the elbow (EL)
    ArmMath oArmMath;
    
public:
    ArmExtender();
    //~ArmExtender();
    
    
private:       
    // prepare arm driver
    virtual void prepareDriver();
    // connect driver to specific joints
    virtual void connectDriver();
    // prepare movement
    virtual void prepareMove();
    // perform movement
    virtual void doMove();
    // read bus data
    virtual void senseBus();
    // write action commands to bus
    virtual void writeBus();
        
    // compute the tilt deviation after the extension stage
    void computeTiltDeviation();                          

};
}
#endif
