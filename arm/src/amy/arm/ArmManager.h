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
#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/bus/JointBus.h"
#include "amy/arm/bus/MovementControl.h"
#include "amy/arm/config/ArmConfig.h"
#include "amy/arm/modules/ArmMover.h"
#include "amy/arm/modules/ArmPanner2.h"
#include "amy/arm/modules/ArmElbow.h"
#include "amy/arm/modules/ArmExtender.h"
#include "amy/arm/modules/JointControl2.h"
#include "amy/arm/coms/ArmComs1.h"
#include "amy/arm/coms/ArmComsOut.h"
#include "amy/robot/Robot.h"
#include "amy/robot/Arm.h"
#include "amy/arm/util/ArmModule.h"

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
        ArmBus oArmBus;
        ArmConfig oArmConfig;
        Arm oArm;       // controlled arm
        MovementControl oMovementControl;   // shared movement control
        int level;      // highest level activated 
        int maxLevel; // allow activation of modules until this level
        // modules ...
        ArmMover oArmMover;
        ArmExtender oArmExtender;
        ArmElbow oArmElbow;
        ArmPanner2 oArmPanner;
        JointControl2 oJointControl2[AMY_MAX_JOINTS];
        ArmComs1 oArmComs;   // communications module for handling of arm control commands & sensor info
        ArmComsOut oArmComsOut;   // communications module for sending outputs to network
        std::vector<ArmModule*> listModules;      // list of modules (pointers)
        // system's IO
        //std::vector<float> listIstAngles;     // ist (sensed) joint angles
        std::vector<float> listSollAngles;  // soll (commanded) joint angles

    public:
        ArmManager();
        ~ArmManager();

       // launches the arm manager to handle the specified robot arm (returns false if something fails)
       bool launch(Robot& oRobot, int targetArm);
       // ends the arm manager
       bool end();

       bool isEnabled() {return benabled;};
                
        // writes sensed joints positions to bus
        void setIstAngles (std::vector<float>& listAngles);
        // reads commanded joints positions from bus
        void readSollAngles();

        // returns the last read commanded angles for all arm joints (in degrees)
        std::vector<float>& getSollAngles() {return listSollAngles;};
        
        // checks if finish command has been requested from console
        bool checkEndRequested();
        
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
    // maps joint buses to IO outputs
    JointBus& mapBus2SystemIO(int i);
};

}    
#endif
