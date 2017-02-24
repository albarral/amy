#ifndef __AMY_ARM_ARMSENSE_H
#define __AMY_ARM_ARMSENSE_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/util/ArmModule3.h"
#include "amy/arm/move/ArmPolarSensor.h"
#include "amy/arm/move/SpeedSensor3.h"

namespace amy
{
// Module that senses the axis positions of the arm.
class ArmSense: public ArmModule3
{
public:
    // states of module
    enum eType
    {
         eSTATE_GO,     // sensing state
    };

protected:
    static log4cxx::LoggerPtr logger;
    // logic
    JointBus* pHSBus;       // bus connection to HS
    JointBus* pVSBus;       // bus connection to VS
    JointBus* pELBus;       // bus connection to ELB
    float istPan;           // computed pan
    float istTilt;            // computed tilt  
    float istRadius;       // computed radius 
    float speedPan;           // computed pan speed (deg/s)
    float speedTilt;            // computed tilt  speed (deg/s)
    float speedRadius;       // computed radius speed  (cm/s))
    ArmPolarSensor oArmPolarSensor; // utility class for axes computations
    SpeedSensor3 oSpeedSensor3;
    float istHS;            // real HS angle (degrees)
    float istVS;            // real VS angle (degrees)
    float istELB;           // real ELB angle (degrees)
    float prevHS;            // previous HS angle
    float prevVS;            // previous VS angle
    float prevELB;           // previous ELB angle
    
private:
    
public:
        ArmSense();
        //~ArmPolarSensing();
                
private:
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        // read bus data   
        virtual void senseBus();
        // write action commands to out joint bus
        virtual void writeBus();
        // show module initialization in logs
        virtual void showInitialized();
        
};
}
#endif
