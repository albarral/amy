#ifndef __AMY_CORE_ARMBUS_H
#define __AMY_CORE_ARMBUS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/core/bus/JointBus.h"
#include "amy/core/brooks/control.h"

namespace amy
{
class ArmBus
{
    private:        
        bool benabled;
        std::string armName;
        
        // CONTROLS (receiver modules)
        // ArmManager
        amy::Control CO_FINISH_MANAGER;    // finish all modules 
        // ArmMover 
        amy::Control CO_ARMMOVER_START;       // ArmMover command: start 
        amy::Control CO_ARMMOVER_STOP;       // ArmMover command: stop
        // AxisDrivers
        //ControlT<float> CO_ARM_T4MOVE;  // time for move (secs)
        ControlT<int> CO_ARM_PAN;       // arm's target pan
        ControlT<int> CO_ARM_TILT;       // arm's target tilt
        ControlT<int> CO_ARM_RADIUS;   // arm's target radius
        // ArmPosition
//        SensorT<int> SO_ARM_PAN;      // arm's real pan
//        SensorT<int> SO_ARM_TILT;      // arm's real tilt
//        SensorT<int> SO_ARM_RADIUS;      // arm's real radius
        
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

        ControlT<int>& getCO_ARM_PAN() {return CO_ARM_PAN;};        
        ControlT<int>& getCO_ARM_TILT() {return CO_ARM_TILT;};        
        ControlT<int>& getCO_ARM_RADIUS() {return CO_ARM_RADIUS;};        
        // sensors
//        SensorT<int>& getSO_ARM_PAN() {return SO_ARM_PAN;};        
//        SensorT<int>& getSO_ARM_TILT() {return SO_ARM_TILT;};        
//        SensorT<int>& getSO_ARM_RADIUS() {return SO_ARM_RADIUS;};        
        
        // joints
        JointBus& getBusHS() {return oBusHS;};
        JointBus& getBusVS() {return oBusVS;};
        JointBus& getBusEL() {return oBusEL;};
        JointBus& getBusHW() {return oBusHW;};
        JointBus& getBusVW() {return oBusVW;};

        // gets the bus section for the specified joint name
        JointBus& getJointBus(std::string jointName);    
        
        std::string toString();
};

}    
#endif
