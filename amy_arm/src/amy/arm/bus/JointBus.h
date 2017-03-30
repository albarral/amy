#ifndef __AMY_ARM_JOINTBUS_H
#define __AMY_ARM_JOINTBUS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/control/brooks/controlT.h"
#include "amy/control/brooks/sensorT.h"

namespace amy
{
// Bus connections for a specific joint.. 
class JointBus
{
    private:        
        bool benabled;
        std::string jointName;

        // CONTROLS 
        ControlT<float> CO_JOINT_ACCEL;         // commanded joint acceleration (degrees/s2)
        ControlT<float> CO_JOINT_ANGLE;         // commanded joint angle (degrees)

        // SENSORS 
        SensorT<float> SO_JOINT_SPEED;               //  internally commanded speed (degrees/s)
        SensorT<int> SO_JOINT_LIMIT_REACHED;     //  joint range limit reached: 0, 1 (top limit), -1 (bottom limit)
        SensorT<float> SO_IST_ANGLE;                 // real joint angle (degrees)
        
    public:
        JointBus();
        //~ConnectionsJoint();
                
        // initializes the class with the given joint name
        void init (std::string jointName);        
        bool isEnabled() {return benabled;};
        std::string& getJointName() {return jointName;};

        // CONTROLS 
        ControlT<float>& getCO_JOINT_ACCEL() {return CO_JOINT_ACCEL;};                
        ControlT<float>& getCO_JOINT_ANGLE() {return CO_JOINT_ANGLE;};                
        
        // SENSORS 
        SensorT<float>& getSO_JOINT_SPEED() {return SO_JOINT_SPEED;}; 
        SensorT<int>& getSO_JOINT_LIMIT_REACHED() {return SO_JOINT_LIMIT_REACHED;}; 
        SensorT<float>& getSO_IST_ANGLE() {return SO_IST_ANGLE;}; 
        
        std::string toString();
};

}    
#endif
