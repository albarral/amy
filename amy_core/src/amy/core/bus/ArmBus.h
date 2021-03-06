#ifndef __AMY_CORE_ARMBUS_H
#define __AMY_CORE_ARMBUS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/core/bus/CyclerBus.h"
#include "amy/core/bus/AxisBus.h"
#include "amy/core/bus/JointBus.h"
#include "tron/control/brooks/control1.h"
#include "amy/core/robot/Arm.h"

namespace amy
{
class ArmBus
{
    private:        
        bool benabled;
        std::string armName;
        
        // CONTROLS 
        tron::Control1 CO_ARM_STOP;       // arm stop

        // connections for all cyclers
        CyclerBus oCyclerBus1;
        CyclerBus oCyclerBus2;
                
        // TiltKeeper
        tron::Control1 CO_KEEP_TILT;    // arm's keep tilt

        // connection for each axis (pan, tilt, radial)
        AxisBus oBusPan;
        AxisBus oBusTilt;
        AxisBus oBusRadial;
                
        // connections for individual joints 
        JointBus oBusHS;    // HS: horiz shoulder 
        JointBus oBusVS;    // VS: vert shoulder 
        JointBus oBusEL;    // EL: elbow 
        JointBus oBusHW;   // HW: horiz wrist
        JointBus oBusVW;   // VW: vert wrist
        int numJoints;   // number of active joints
        
    public:
        ArmBus();
        //~ArmBus();
        
        void init(Arm& oArm);
        
        int getNumJoints() {return numJoints;};
        bool isEnabled() {return benabled;};
        
        // CONTROLS
        tron::Control1& getCO_ARM_STOP() {return CO_ARM_STOP;};        
        
        // CONTROLS & SENSORS for cyclers
        CyclerBus& getCyclerBus1() {return oCyclerBus1;};
        CyclerBus& getCyclerBus2() {return oCyclerBus2;};

        // TiltKeeper
        tron::Control1& getCO_KEEP_TILT() {return CO_KEEP_TILT;};
        
        // CONTROLS & SENSORS for axes
        AxisBus& getPanBus() {return oBusPan;};
        AxisBus& getTiltBus() {return oBusTilt;};
        AxisBus& getRadialBus() {return oBusRadial;};        
                
        // CONTROLS & SENSORS for joints
        JointBus& getBusHS() {return oBusHS;};
        JointBus& getBusVS() {return oBusVS;};
        JointBus& getBusEL() {return oBusEL;};
        JointBus& getBusHW() {return oBusHW;};
        JointBus& getBusVW() {return oBusVW;};
        
        std::string toString();
};

}    
#endif
