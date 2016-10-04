#ifndef __AMY_ARM_JOINTBUS_H
#define __AMY_ARM_JOINTBUS_H

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
        ControlT<int> CO_JMOVER_ACTION;         // >> JointMover: action requests (move, brake, keep, stop)
        ControlT<int> CO_JMOVER_ACCEL;         // >> JointMover: required acceleration
        ControlT<float> CO_JCONTROL_SPEED;    // >> JointControl: desired joint speed (degrees/s)
        ControlT<float> CO_JOINT_ANGLE;         // >> real arm: desired joint angle (degrees)

        // SENSORS 
        SensorT<float> SO_IST_ANGLE;            // real arm >> real joint angle (degrees)
        SensorT<float> SO_REAL_SPEED;        //  JointControl >> real joint speed (degrees/s)
        SensorT<int> SO_LIMIT_REACHED;      //  JointControl >> range limit reached: 0, 1 (top limit), -1 (bottom limit)
        
    public:
        JointBus();
        //~ConnectionsJoint();
                
        // initializes the class with the given joint name
        void init (std::string jointName);        
        bool isEnabled() {return benabled;};
        std::string& getJointName() {return jointName;};

        // controls
        ControlT<int>& getCO_JMOVER_ACTION() {return CO_JMOVER_ACTION;};        
        ControlT<int>& getCO_JMOVER_ACCELERATION() {return CO_JMOVER_ACCEL;};        
        ControlT<float>& getCO_JCONTROL_SPEED() {return CO_JCONTROL_SPEED;};                
        ControlT<float>& getCO_JOINT_ANGLE() {return CO_JOINT_ANGLE;};                
        
        // sensors
        SensorT<float>& getSO_IST_ANGLE() {return SO_IST_ANGLE;}; 
        SensorT<float>& getSO_REAL_SPEED() {return SO_REAL_SPEED;}; 
        SensorT<int>& getSO_LIMIT_REACHED() {return SO_LIMIT_REACHED;}; 
        
        std::string toString();
};

}    
#endif
