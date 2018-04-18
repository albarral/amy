#ifndef __AMY_CORE_JOINTBUS_H
#define __AMY_CORE_JOINTBUS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "tron/control/brooks/control3.h"
#include "tron/control/brooks/sensor2.h"
#include "tron/control/brooks/sensor3.h"

namespace amy
{
// Bus connections for a specific joint.. 
class JointBus
{
    private:        
        bool benabled;
        std::string jointName;

        // CONTROLS 
        tron::Control3 CO_JOINT_ACCEL;         // commanded joint acceleration (degrees/s2)
        tron::Control3 CO_JOINT_ANGLE;         // commanded joint angle (degrees)

        // SENSORS 
        tron::Sensor2 SO_DRIVER_STATE;               //  state of JointDriver module
        tron::Sensor3 SO_JOINT_SPEED;               //  internally commanded speed (degrees/s)
        tron::Sensor2 SO_JOINT_LIMIT_REACHED;     //  joint range limit reached: 0, 1 (top limit), -1 (bottom limit)
        tron::Sensor3 SO_IST_ANGLE;                 // real joint angle (degrees)
        
    public:
        JointBus();
        //~ConnectionsJoint();
                
        // initializes the class with the given joint name
        void init (std::string jointName);        
        bool isEnabled() {return benabled;};
        std::string& getJointName() {return jointName;};

        // CONTROLS 
        tron::Control3& getCO_JOINT_ACCEL() {return CO_JOINT_ACCEL;};                
        tron::Control3& getCO_JOINT_ANGLE() {return CO_JOINT_ANGLE;};                
        
        // SENSORS 
        tron::Sensor2& getSO_DRIVER_STATE() {return SO_DRIVER_STATE;}; 
        tron::Sensor3& getSO_JOINT_SPEED() {return SO_JOINT_SPEED;}; 
        tron::Sensor2& getSO_JOINT_LIMIT_REACHED() {return SO_JOINT_LIMIT_REACHED;}; 
        tron::Sensor3& getSO_IST_ANGLE() {return SO_IST_ANGLE;}; 
        
        std::string toString();
};

}    
#endif
