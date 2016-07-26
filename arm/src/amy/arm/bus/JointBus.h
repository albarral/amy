#ifndef __SAM_MANIPULATION_CONNECTIONS_JOINT_H
#define __SAM_MANIPULATION_CONNECTIONS_JOINT_H

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

        // CONTROLS (receiver modules)
        // JointMover 
        amy::ControlT<int> CO_JMOVER_ACTION;     // UP >> JointMover: received actions (move, brake, keep, stop)
        // JointControl 
        amy::ControlT<float> CO_JCONTROL_SPEED;    // JointMover >> JointControl: desired joint speed (degrees/s)
        // ArmManager
        amy::ControlT<float> CO_JOINT_ANGLE;         // desired joint angle (degrees)

        // SENSORS (sender modules)        
        // ArmManager 
        amy::SensorT<float> SO_IST_ANGLE;            // real joint angle (degrees)
        // JointControl 
        amy::SensorT<float> SO_REAL_SPEED;     // real joint speed (degrees/s)
        amy::SensorT<int> SO_LIMIT_REACHED;     // range limit reached: 0, 1 (top limit), -1 (bottom limit)
        
    public:
        JointBus();
        //~ConnectionsJoint();
                
        // initializes the class with the given joint name
        void init (std::string jointName);        
        bool isEnabled() {return benabled;};
        std::string& getJointName() {return jointName;};

        // controls
        amy::ControlT<int>& getCO_JMOVER_ACTION() {return CO_JMOVER_ACTION;};        
        amy::ControlT<float>& getCO_JCONTROL_SPEED() {return CO_JCONTROL_SPEED;};                
        amy::ControlT<float>& getCO_JOINT_ANGLE() {return CO_JOINT_ANGLE;};                
        
        // sensors
        amy::SensorT<float>& getSO_IST_ANGLE() {return SO_IST_ANGLE;}; 
        amy::SensorT<float>& getSO_REAL_SPEED() {return SO_REAL_SPEED;}; 
        amy::SensorT<int>& getSO_LIMIT_REACHED() {return SO_LIMIT_REACHED;}; 
};

}    
#endif
