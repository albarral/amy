#ifndef __AMY_CORE_ARMBUS_H
#define __AMY_CORE_ARMBUS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/arm/bus/JointBus.h"
#include "amy/control/brooks/control.h"
#include "amy/core/robot/Arm.h"

namespace amy
{
class ArmBus
{
    private:        
        bool benabled;
        std::string armName;
        
        // CONTROLS 
        ControlT<bool> CO_ARM_STOP;       // arm stop
        // ArmMover 
        amy::Control CO_ARMMOVER_START;       // ArmMover command: start 
        amy::Control CO_ARMMOVER_STOP;       // ArmMover command: stop
        // AxisCyclers (pan, tilt, radial)
        ControlT<float> CO_PAN_FREQUENCY;    // pan's cyclic frequency (Hz)
        ControlT<float> CO_PAN_AMPLITUDE;    // degrees
        ControlT<bool> CO_PAN_TRIGGER;        // start cyclic move  
        ControlT<bool> CO_PAN_STOP;            // stop cyclic move 
        ControlT<float> CO_TILT_FREQUENCY;    // pan's cyclic frequency (Hz)
        ControlT<float> CO_TILT_AMPLITUDE;    // degrees
        ControlT<bool> CO_TILT_TRIGGER;        // start cyclic move  
        ControlT<bool> CO_TILT_STOP;            // stop cyclic move 
        // AxisRacers (pan, tilt, radial)
        ControlT<float> CO_PAN_SPEED;       // arm's pan speed (deg/s)
        ControlT<float> CO_TILT_SPEED;       // arm's tilt speed (deg/s)
        ControlT<float> CO_RADIAL_SPEED;   // arm's radial speed (cm/s)
        // TiltKeeper
        ControlT<bool> CO_KEEP_TILT;    // arm's keep tilt
        // AxisDrivers (pan, tilt, radial)
        ControlT<int> CO_ARM_PAN;       // arm's target pan
        ControlT<int> CO_ARM_TILT;       // arm's target tilt
        ControlT<int> CO_ARM_RADIUS;   // arm's target radius
        
        // SENSORS
        // ArmSense
        SensorT<float> SO_ARM_PAN;      // arm's real pan
        SensorT<float> SO_ARM_TILT;      // arm's real tilt
        SensorT<float> SO_ARM_RADIUS;  // arm's real radius
        SensorT<float> SO_PAN_SPEED;         // pan speed (deg/s)
        SensorT<float> SO_TILT_SPEED;         // tilt speed (deg/s)
        SensorT<float> SO_RADIAL_SPEED;     // radius speed (deg/s)
        
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
        ControlT<bool>& getCO_ARM_STOP() {return CO_ARM_STOP;};
        // ArmMover 
        amy::Control& getCO_ARMMOVER_START() {return CO_ARMMOVER_START;};        
        amy::Control& getCO_ARMMOVER_STOP() {return CO_ARMMOVER_STOP;};        
        // AxisCyclers (pan, tilt, radial)
        ControlT<float>& getCO_PAN_FREQUENCY() {return CO_PAN_FREQUENCY;};   
        ControlT<float>& getCO_PAN_AMPLITUDE() {return CO_PAN_AMPLITUDE;};   
        ControlT<bool>& getCO_PAN_TRIGGER() {return CO_PAN_TRIGGER;};
        ControlT<bool>& getCO_PAN_STOP() {return CO_PAN_STOP;};
        ControlT<float>& getCO_TILT_FREQUENCY() {return CO_TILT_FREQUENCY;};   
        ControlT<float>& getCO_TILT_AMPLITUDE() {return CO_TILT_AMPLITUDE;};   
        ControlT<bool>& getCO_TILT_TRIGGER() {return CO_TILT_TRIGGER;};
        ControlT<bool>& getCO_TILT_STOP() {return CO_TILT_STOP;};
        // AxisRacers (pan, tilt, radial)
        ControlT<float>& getCO_PAN_SPEED() {return CO_PAN_SPEED;};        
        ControlT<float>& getCO_TILT_SPEED() {return CO_TILT_SPEED;};        
        ControlT<float>& getCO_RADIAL_SPEED() {return CO_RADIAL_SPEED;};        
        // TiltKeeper
        ControlT<bool>& getCO_KEEP_TILT() {return CO_KEEP_TILT;};
        // AxisDrivers (pan, tilt, radial)
        ControlT<int>& getCO_ARM_PAN() {return CO_ARM_PAN;};        
        ControlT<int>& getCO_ARM_TILT() {return CO_ARM_TILT;};        
        ControlT<int>& getCO_ARM_RADIUS() {return CO_ARM_RADIUS;};        
        
        // SENSORS
        // ArmSense
        SensorT<float>& getSO_ARM_PAN() {return SO_ARM_PAN;};        
        SensorT<float>& getSO_ARM_TILT() {return SO_ARM_TILT;};        
        SensorT<float>& getSO_ARM_RADIUS() {return SO_ARM_RADIUS;};        
        SensorT<float>& getSO_PAN_SPEED() {return SO_PAN_SPEED;};
        SensorT<float>& getSO_TILT_SPEED() {return SO_TILT_SPEED;};            
        SensorT<float>& getSO_RADIAL_SPEED() {return SO_RADIAL_SPEED;};
        
        // JointDriver's CONTROLS & SENSORS
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
