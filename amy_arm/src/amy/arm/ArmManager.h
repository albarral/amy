#ifndef __AMY_ARM_MANAGER_H
#define __AMY_ARM_MANAGER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "amy/arm/config/ArmDefines.h"
#include "amy/arm/config/ArmConfig.h"
#include "amy/arm/modules/ArmMover.h"
#include "amy/arm/modules/ArmPanner2.h"
#include "amy/arm/modules/ArmElbow.h"
#include "amy/arm/modules/ArmExtender.h"
#include "amy/arm/modules/JointControl2.h"
#include "amy/arm/util/ArmModule.h"
#include "amy/core/bus/ArmBus.h"
#include "amy/core/bus/MovementControl.h"
#include "amy/core/robot/Arm.h"

namespace amy
{
// This class manages a robot's arm.
// It is composed of various modules, each running its own thread. 
// Modules are distributed on levels.     
class ArmManager
{
    private:
        static log4cxx::LoggerPtr logger;
        bool benabled;
        ArmConfig oArmConfig;
        Arm oArm;       // controlled arm
        ArmBus* pArmBus;        // access to arm bus
        MovementControl oMovementControl;   // shared movement control
        int level;      // highest level activated 
        int maxLevel; // allow activation of modules until this level
        // modules ...
        ArmMover oArmMover;
        ArmExtender oArmExtender;
        ArmElbow oArmElbow;
        ArmPanner2 oArmPanner;
        JointControl2 oJointControl2[AMY_MAX_JOINTS];
        std::vector<ArmModule*> listModules;      // list of modules (pointers)

    public:
        ArmManager();
        ~ArmManager();

       // launches the arm manager to handle the specified robot arm (returns false if something fails)
       bool launch(ArmBus& oArmBus, Arm& oArm);
       // ends the arm manager
       bool end();

       bool isEnabled() {return benabled;};                
        
private:
    // initialize control architecture (organize in levels)
    void initArchitecture();
    // show description of control architecture
    void showArchitecture();

    // initializes bus and modules
    void init();        
    // starts the task's modules 
    void startModules();        
    // stops the tasks' modules
    void stopModules();        
    
    void initBus(std::vector<std::string>& listJointNames);
    void initModules();
    
   // init the modules of a level
    void initLevel(int level);        
   // start the modules of a level
    void startLevel(int level);        
   // stop the modules of a level
    void stopLevel(int level);        
};

}    
#endif
