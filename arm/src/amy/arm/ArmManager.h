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
#include "amy/arm/config/ArmConfig.h"
#include "amy/arm/data/Arm.h"
#include "amy/arm/modules/ArmMover.h"
#include "amy/arm/modules/JointMover.h"
#include "amy/arm/modules/JointControl.h"
#include "amy/arm/coms/ArmComs1.h"
#include "amy/arm/coms/ArmComsOut.h"

namespace amy
{
// This class manages a robot's arm.
// It is composed of various modules, each running its own thread.     
class ArmManager
{
    private:
        static log4cxx::LoggerPtr logger;
        bool benabled;
        ArmBus oArmBus;
        ArmConfig oArmConfig;
        Arm oArm;
        int level;      // modules level activated 
        // modules ...
        ArmMover oArmMover;
        JointMover oJointMover[AMY_MAX_JOINTS];
        JointControl oJointControl[AMY_MAX_JOINTS];
        ArmComs1 oArmComs;   // communications module for handling of arm control commands & sensor info
        ArmComsOut oArmComsOut;   // communications module for sending outputs to network
        // system's IO
        //std::vector<float> listIstAngles;     // ist (sensed) joint angles
        std::vector<float> listSollAngles;  // soll (commanded) joint angles

    public:
        ArmManager();
        ~ArmManager();

        // initializes everything (arm, bus & modules). 
       void init(std::string robotName);        
       bool isEnabled() {return benabled;};

       // starts the task's modules 
        void startModules();        
        // stops the tasks' modules
        void stopModules();        
        
        // writes sensed joints positions to bus
        void setIstAngles (std::vector<float>& listAngles);
        // reads commanded joints positions from bus
        void readSollAngles();

        // returns the last read commanded angles for all arm joints (in degrees)
        std::vector<float>& getSollAngles() {return listSollAngles;};
        
        // checks if finish command has been requested from console
        bool checkEndRequested();
        
private:
    void initArm(std::vector<std::string>& listJointNames);
    void initBus(std::vector<std::string>& listJointNames);
    void initModules(std::vector<std::string>& listJointNames);
};

}    
#endif
