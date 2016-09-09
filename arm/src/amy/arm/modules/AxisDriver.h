#ifndef __AMY_ARM_AXISDRIVER_H
#define __AMY_ARM_AXISDRIVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>
#include "amy/arm/bus/ArmBus.h"
#include "amy/utils/module2.h"

namespace amy
{
// Behaviour used to move an arm to a target position. Used for a single direction: pan, tilt or radial.
// Designed as BASIC CLASS to be extended ...   
// Movements done in 3 stages: 
// DRIVE:           high speed      (far from target))
// APPROACH;    lower speed    (near to target)
// ARRIVED:        stop               (at target, with tolerance)  
// FREE:            (special state) leaves arm free, no control done
// 4 params:
// dH: distance that separates DRIVE & APPROACH states
// dL: pos tolerance for ARRIVED state
// vH: high speed used on DRIVE
// vL: low speed used on APPROACH
// Outputs:
// DRIVE:            FOR & BAC
// APPROACH:      BRAKE & KEEP
// ARRIVED:          STOP 
class AxisDriver: public Module2
{
public:
    // states of AxisDriver module
    enum eType
    {
         eSTATE_FREE,
         eSTATE_ARRIVED,
         eSTATE_APPROACH,
         eSTATE_DRIVE
    };

protected:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    // params
    std::string modName;   // module name
    int dH;
    int dL;
    int vH;
    int vL;
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pBus;
    // logic
    float istValue;
    int targetValue;
    int outAction;
    int outSpeed;
    

public:
        AxisDriver();
        //~AxisDriver();
                
       // module params
       void init(int dH, int dL, int vH, int vL);
       bool isEnabled() {return benabled;};

       // bus connection 
       void connect(ArmBus& oBus);
       bool isConnected() {return bconnected;};
       
               
protected:       
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        
        virtual void selectBusJoint() = 0;
        // read bus data
        virtual void senseBus() = 0;
        // write action commands to bus
        virtual void writeBus() = 0;
        
        virtual void doDriveControl(float dist) = 0;
        virtual void doApproachControl(float dist) = 0;
        virtual void doArrivedControl(float dist) = 0;
        
        // shows the present state name
        void showState();
};
}
#endif
