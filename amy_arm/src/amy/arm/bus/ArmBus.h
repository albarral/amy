#ifndef __AMY_CORE_ARMBUS_H
#define __AMY_CORE_ARMBUS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/arm/bus/JointBus.h"
#include "amy/utils/brooks/control.h"
#include "amy/core/robot/Arm.h"

namespace amy
{
class ArmBus
{
    private:        
        bool benabled;
        std::string armName;
        
        // CONTROLS 
        // ArmMover 
        amy::Control CO_ARMMOVER_START;       // ArmMover command: start 
        amy::Control CO_ARMMOVER_STOP;       // ArmMover command: stop
        // AxisDrivers
        ControlT<int> CO_ARM_PAN;       // arm's target pan
        ControlT<int> CO_ARM_TILT;       // arm's target tilt
        ControlT<int> CO_ARM_RADIUS;   // arm's target radius
        // SpeedDrivers
        ControlT<bool> CO_KEEP_TILT;    // arm's keep tilt
        
        // SENSORS
        // ArmPosition
        SensorT<float> SO_ARM_PAN;      // arm's real pan
        SensorT<float> SO_ARM_TILT;      // arm's real tilt
        SensorT<float> SO_ARM_RADIUS;  // arm's real radius
        
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
        amy::Control& getCO_ARMMOVER_START() {return CO_ARMMOVER_START;};        
        amy::Control& getCO_ARMMOVER_STOP() {return CO_ARMMOVER_STOP;};        

        ControlT<int>& getCO_ARM_PAN() {return CO_ARM_PAN;};        
        ControlT<int>& getCO_ARM_TILT() {return CO_ARM_TILT;};        
        ControlT<int>& getCO_ARM_RADIUS() {return CO_ARM_RADIUS;};        

        ControlT<bool>& getCO_KEEP_TILT() {return CO_KEEP_TILT;};
        
        // SENSORS
        SensorT<float>& getSO_ARM_PAN() {return SO_ARM_PAN;};        
        SensorT<float>& getSO_ARM_TILT() {return SO_ARM_TILT;};        
        SensorT<float>& getSO_ARM_RADIUS() {return SO_ARM_RADIUS;};        
        
        // joints
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
