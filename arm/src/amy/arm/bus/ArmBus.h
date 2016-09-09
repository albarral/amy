#ifndef __AMY_ARM_BUS_H
#define __AMY_ARM_BUS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/arm/config/ArmDefines.h"
#include "amy/arm/bus/JointBus.h"
#include "amy/utils/brooks/control.h"

namespace amy
{
class ArmBus
{
    private:        
        bool benabled;
        
        // CONTROLS (receiver modules)
        // ArmManager
        amy::Control CO_FINISH_MANAGER;    // finish all modules 
        // ArmMover 
        amy::Control CO_ARMMOVER_START;       // ArmMover command: start 
        amy::Control CO_ARMMOVER_STOP;       // ArmMover command: stop
        // Wrist mover
        ControlT<float> CO_WRIST_PAN;       // target radius for the wrist
        ControlT<float> CO_WRIST_TILT;       // target radius for the wrist
        ControlT<float> CO_WRIST_RADIUS;       // target radius for the wrist
        
        // connections for individual joints 
        JointBus oBusHS;    // HS: horiz shoulder 
        JointBus oBusVS;    // VS: vert shoulder 
        JointBus oBusEL;    // EL: elbow 
        JointBus oBusHW;   // HW: horiz wrist
        JointBus oBusVW;   // VW: vert wrist
        int numJoints;   // number of active joints
        
    public:
        ArmBus();
        //~Connections();

        // initializes a JointBus object for the given joint name. Returns true if ok, false otherwise.
        bool addJointBus(std::string jointName);
        int getNumJoints() {return numJoints;};
        bool isEnabled() {return benabled;};
        
        // controls
        amy::Control& getCO_FINISH_MANAGER() {return CO_FINISH_MANAGER;};   
        amy::Control& getCO_ARMMOVER_START() {return CO_ARMMOVER_START;};        
        amy::Control& getCO_ARMMOVER_STOP() {return CO_ARMMOVER_STOP;};        
        ControlT<float>& getCO_WRIST_RADIUS() {return CO_WRIST_RADIUS;};        
        // joints
        JointBus& getBusHS() {return oBusHS;};
        JointBus& getBusVS() {return oBusVS;};
        JointBus& getBusEL() {return oBusEL;};
        JointBus& getBusHW() {return oBusHW;};
        JointBus& getBusVW() {return oBusVW;};

        // gets the bus section for the specified joint name
        JointBus& getJointBus(std::string jointName);                
};

}    
#endif
