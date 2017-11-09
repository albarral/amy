#ifndef __AMY_ARM_MANAGER_H
#define __AMY_ARM_MANAGER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "amy/core/bus/ArmBus.h"
#include "amy/core/config/AmyConfig.h"
#include "amy/core/robot/Arm.h"
#include "amy/arm/config/ArmConfig.h"
#include "amy/arm/modules/ArmMover.h"
#include "amy/arm/modules/FrontalCycler.h"
#include "amy/arm/modules/PanRacer.h"
#include "amy/arm/modules/TiltRacer.h"
#include "amy/arm/modules/RadialRacer.h"
#include "amy/arm/modules/TiltKeeper.h"
#include "amy/arm/modules/PanDriver.h"
#include "amy/arm/modules/TiltDriver.h"
#include "amy/arm/modules/RadiusDriver.h"
#include "amy/arm/modules/ArmSense.h"
#include "amy/arm/modules/JointDriver.h"
#include "amy/arm/util/ArmModule.h"
#include "amy/arm/util/ArmModule3.h"

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
        AmyConfig oAmyConfig;        
        Arm* pArm;                   // access to controlled arm
        ArmBus* pArmBus;        // access to arm bus
        AmyConfig* pAmyConfig;  // acces to amy config
        ArmConfig oArmConfig;     // arm configuration
        int topLevel; // allow activation of modules until this level
        // modules ...
        // level 4
        ArmMover oArmMover;
        FrontalCycler oFrontalCycler;
        // level 3
        PanRacer oPanRacer;
        TiltRacer oTiltRacer;
        RadialRacer oRadialRacer;
        // level 2
        TiltKeeper oTiltKeeper;
        PanDriver oPanDriver;
        TiltDriver oTiltDriver;
        RadiusDriver oRadiusDriver;
        ArmSense oArmSense;
        // level 1
        JointDriver oJointDriver[AMY_MAX_JOINTS];
        std::vector<ArmModule*> listModules;      // list of modules (pointers)
        std::vector<ArmModule3*> listModules3;   // list of modules (pointers)

    public:
        ArmManager();
        ~ArmManager();

       // launches the arm manager to handle the specified robot arm (returns false if something fails)
       bool launch(ArmBus& oArmBus, Arm& oArm);
       // ends the arm manager
       bool end();
       bool isLaunched() {return blaunched;};                
       
       friend class ArmTest;
       
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
