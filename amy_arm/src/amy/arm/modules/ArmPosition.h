#ifndef __AMY_ARM_ARMPOSITION_H
#define __AMY_ARM_ARMPOSITION_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/util/ArmModule3.h"
#include "amy/arm/move/AxesSensor.h"

namespace amy
{
// Module that senses the axis positions of the arm.
class ArmPosition: public ArmModule3
{
public:
    // states of ArmPosition module
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
    float istHS;            // real HS angle (degrees)
    float istVS;            // real VS angle (degrees)
    float istELB;           // real ELB angle (degrees)
    float istPan;           // computed pan
    float istTilt;            // computed tit  
    float istRadius;       // computed radius 
    AxesSensor oAxesSensor; // utility class for axes computations
    float prevHS;            // previous HS angle
    float prevVS;            // previous VS angle
    float prevELB;           // previous ELB angle
    
private:
    
public:
        ArmPosition();
        //~ArmPosition();
                
private:
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        // read bus data   
        virtual void senseBus();
        // write action commands to out joint bus
        void writeBus();
};
}
#endif
