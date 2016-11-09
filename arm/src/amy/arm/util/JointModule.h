#ifndef __AMY_JOINT_MODULE_H
#define __AMY_JOINT_MODULE_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/arm/util/ArmModule.h"
#include "amy/arm/bus/JointBus.h"

namespace amy
{
// Base class for amy arm modules associated to a single joint.
// It's associated to a hierarchical level & holds a connection to a JointBus.
// usage: set target joint, set level, init, connect and on
class JointModule : public ArmModule
{  
protected:
    std::string jointName;    // name of the controlled joint  
    // bus
    JointBus* pJointBus;    // bus connection for the controlled joint

public:
        JointModule();
        //~JointModule();
                
        void setTargetJoint(std::string name); 
        
       // bus connection               
       virtual void connect(ArmBus& oArmBus);              
};
}
#endif
