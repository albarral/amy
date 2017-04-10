#ifndef __AMY_ARM_ARMBUS_H
#define __AMY_ARM_ARMBUS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/arm/bus/AxisBus.h"
#include "amy/arm/bus/JointBus.h"
#include "amy/control/brooks/controlT.h"
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
        
        // Frontal cycler 
        ControlT<float> CO_FRONT_FREQ;              // movement frequency
        ControlT<float> CO_FRONT_AMPLITUDE;      // movement amplitude (degrees)
        ControlT<float> CO_FRONT_ANGLE;            // movement orientation (degrees)
        ControlT<bool> CO_FRONT_ACTION;           // start/stop movement
                
        // TiltKeeper
        ControlT<bool> CO_KEEP_TILT;    // arm's keep tilt

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
        ControlT<bool>& getCO_ARM_STOP() {return CO_ARM_STOP;};
        
        // Frontal cycler
        ControlT<float>& getCO_FRONT_FREQ() {return CO_FRONT_FREQ;};        
        ControlT<float>& getCO_FRONT_AMPLITUDE() {return CO_FRONT_AMPLITUDE;};        
        ControlT<float>& getCO_FRONT_ANGLE() {return CO_FRONT_ANGLE;};        
        ControlT<bool>& getCO_FRONT_ACTION() {return CO_FRONT_ACTION;};        

        // TiltKeeper
        ControlT<bool>& getCO_KEEP_TILT() {return CO_KEEP_TILT;};
        
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
