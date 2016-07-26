#ifndef __SAM_MANIPULATION_BUS_H
#define __SAM_MANIPULATION_BUS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/arm/config/defines.h"
#include "amy/arm/bus/JointBus.h"
#include "amy/utils/brooks/control.h"

namespace amy
{
class ArmBus
{
    private:        
        bool benabled;
        
        // CONTROLS (receiver modules)
        // ArmManager
        amy::Control CO_FINISH_MANAGER;    // finish all modules 
        // ArmMover 
        amy::Control CO_ARMMOVER_START;       // ArmMover command: start 
        amy::Control CO_ARMMOVER_STOP;       // ArmMover command: stop
        
        // connections for individual joints 
        JointBus oJointBus[SAM_MAX_JOINTS];
        int numJoints;   // number of active joints
        
    public:
        ArmBus();
        //~Connections();

        // initializes a JointBus object for the given joint name. Returns true if ok, false otherwise.
        bool add4Joint(std::string jointName);
        int getNumJoints() {return numJoints;};
        bool isEnabled() {return benabled;};
        
        // controls
        amy::Control& getCO_FINISH_MANAGER() {return CO_FINISH_MANAGER;};   
        amy::Control& getCO_ARMMOVER_START() {return CO_ARMMOVER_START;};        
        amy::Control& getCO_ARMMOVER_STOP() {return CO_ARMMOVER_STOP;};        
        
        // gets the bus section for the specified joint name
        JointBus& getJointBus(std::string jointName);
        // gets the bus section for the specified joint index        
        JointBus& getJointBusByIndex(int index);
        
      
private:
    // checks if the given joint name is already used
    bool checkExistingJoint(std::string jointName);
};

}    
#endif
