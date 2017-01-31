#ifndef __AMY_ARM_MANAGER_H
#define __AMY_ARM_MANAGER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/modules/PanDriver.h"
#include "amy/arm/modules/TiltDriver.h"
#include "amy/arm/modules/RadiusDriver.h"
//#include "amy/arm/modules/ArmExtender.h"
#include "amy/arm/modules/ArmPosition.h"
#include "amy/arm/modules/JointDriver.h"
#include "amy/arm/ArmInterface.h"
#include "amy/arm/util/ArmModule.h"
#include "amy/core/config/AmyConfig.h"
#include "amy/core/robot/Arm.h"


#define AMY_MAX_JOINTS 5

namespace amy
{
// This class manages a robot's arm.
// It is composed of various modules, each running its own thread. 
// Modules are distributed on levels.     
class ArmManager
{
    private:
        static log4cxx::LoggerPtr logger;
        bool blaunched;     // indicates when the manager has been launched
        AmyConfig* pAmyConfig;  // acces to amy config
        ArmBus oArmBus;        // arm bus
        Arm oArm;       // controlled arm
        ArmInterface oArmInterface;     // interface for external arm control
        int level;      // highest level activated 
        int maxLevel; // allow activation of modules until this level
        // modules ...
        //ArmMover oArmMover;
        //ArmExtender oArmExtender;
        PanDriver oPanDriver;
        TiltDriver oTiltDriver;
        RadiusDriver oRadiusDriver;
        ArmPosition oArmPosition;
        JointDriver oJointDriver[AMY_MAX_JOINTS];
        std::vector<ArmModule*> listModules;      // list of modules (pointers)

    public:
        ArmManager();
        ~ArmManager();

       // launches the arm manager to handle the specified robot arm (returns false if something fails)
       bool launch(AmyConfig& oAmyConfig, Arm& oArm);
       // ends the arm manager
       bool end();
       bool isLaunched() {return blaunched;};                
       
       // give access to the arm's control interface
       ArmInterface& getArmInterface() {return oArmInterface;}
       
private:
    // initialize control architecture (organize in levels)
    void initArchitecture();
    // show description of control architecture
    void showArchitecture();

    // initialize modules
    void initModules();
    // starts the task's modules 
    void startModules();        
    // stops the tasks' modules
    void stopModules();        
    
    
   // init the modules of a level
    void initLevel(int level);        
   // start the modules of a level
    void startLevel(int level);        
   // stop the modules of a level
    void stopLevel(int level);        
};

}    
#endif
