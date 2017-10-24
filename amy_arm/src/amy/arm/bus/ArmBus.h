#ifndef __AMY_ARM_ARMBUS_H
#define __AMY_ARM_ARMBUS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/arm/bus/CyclerBus.h"
#include "amy/arm/bus/AxisBus.h"
#include "amy/arm/bus/JointBus.h"
#include "tuly/control/brooks/controlT.h"
#include "amy/core/robot/Arm.h"

namespace amy
{
class ArmBus
{
    private:        
        bool benabled;
        std::string armName;
        
        // CONTROLS 
        tuly::ControlT<bool> CO_ARM_STOP;       // arm stop

        // ArmMover
        tuly::ControlT<int> CO_MOVER_TYPE;       // set movement type
        tuly::ControlT<bool> CO_MOVER_ACTION;    // start/stop movement
        tuly::ControlT<int> CO_MOVER_TURN;       // change movement orientation
        tuly::ControlT<bool> CO_MOVER_WIDER;    // change movement width
        tuly::ControlT<bool> CO_MOVER_TALLER;    // change movement height
        tuly::ControlT<bool> CO_MOVER_FASTER;    // change movement speed

        // connections for all cyclers
        CyclerBus oFrontalCyclerBus;
                
        // TiltKeeper
        tuly::ControlT<bool> CO_KEEP_TILT;    // arm's keep tilt

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
        tuly::ControlT<bool>& getCO_ARM_STOP() {return CO_ARM_STOP;};        

        // ArmMover
        tuly::ControlT<int>& getCO_MOVER_TYPE() {return CO_MOVER_TYPE;};
        tuly::ControlT<bool>& getCO_MOVER_ACTION() {return CO_MOVER_ACTION;};
        tuly::ControlT<int>& getCO_MOVER_TURN() {return CO_MOVER_TURN;};
        tuly::ControlT<bool>& getCO_MOVER_WIDER() {return CO_MOVER_WIDER;};
        tuly::ControlT<bool>& getCO_MOVER_TALLER() {return CO_MOVER_TALLER;};
        tuly::ControlT<bool>& getCO_MOVER_FASTER() {return CO_MOVER_FASTER;};
        
        // CONTROLS & SENSORS for cyclers
        CyclerBus& getFrontalCyclerBus() {return oFrontalCyclerBus;};

        // TiltKeeper
        tuly::ControlT<bool>& getCO_KEEP_TILT() {return CO_KEEP_TILT;};
        
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

        // gets the bus section for the specified joint name
        JointBus& getJointBus(std::string jointName);    
        
        std::string toString();

private:
        // initializes a JointBus object for the given joint name. Returns true if ok, false otherwise.
        bool addJointBus(std::string jointName);
};

}    
#endif
