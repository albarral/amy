#ifndef __AMY_CORE_JOINTBUS_H
#define __AMY_CORE_JOINTBUS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/utils/brooks/controlT.h"
#include "amy/utils/brooks/sensorT.h"

namespace amy
{
// Set of bus connections for a specific joint. 
// All modules controlling this joint must be connected through this bus section.
class JointBus
{
    private:        
        bool benabled;
        std::string jointName;

        // CONTROLS 
        ControlT<float> CO_JCONTROL_ACCEL;    // >> JointControl: commanded acceleration (degrees/s2)
        ControlT<float> CO_JOINT_ANGLE;         // >> arm: commanded joint angle (degrees)

        // SENSORS 
        SensorT<float> SO_JCONTROL_SPEED;               //  JointControl >> internally commanded speed (degrees/s)
        SensorT<int> SO_JCONTROL_LIMIT_REACHED;     //  JointControl >> range limit reached: 0, 1 (top limit), -1 (bottom limit)
        SensorT<float> SO_IST_ANGLE;            // real arm >> real joint angle (degrees)
        
    public:
        JointBus();
        //~ConnectionsJoint();
                
        // initializes the class with the given joint name
        void init (std::string jointName);        
        bool isEnabled() {return benabled;};
        std::string& getJointName() {return jointName;};

        // CONTROLS 
        //
        ControlT<float>& getCO_JCONTROL_ACCEL() {return CO_JCONTROL_ACCEL;};                
        //
        ControlT<float>& getCO_JOINT_ANGLE() {return CO_JOINT_ANGLE;};                
        
        // SENSORS 
        SensorT<float>& getSO_JCONTROL_SPEED() {return SO_JCONTROL_SPEED;}; 
        SensorT<int>& getSO_JCONTROL_LIMIT_REACHED() {return SO_JCONTROL_LIMIT_REACHED;}; 
        //
        SensorT<float>& getSO_IST_ANGLE() {return SO_IST_ANGLE;}; 
        
        std::string toString();
};

}    
#endif
