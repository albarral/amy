#ifndef __AMY_ARM_CONFIG_H
#define __AMY_ARM_CONFIG_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "amy/arm/config/ArmDefines.h"
#include "amy/arm/config/ParamsJoint.h"
#include "amy/arm/config/ArmVersion.h"

namespace amy
{
class ArmConfig 
{
public:
    static const std::string horizontal_shoulder;
    static const std::string vertical_shoulder;
    static const std::string elbow;
    static const std::string horizontal_wrist;
    static const std::string vertical_wrist;
    
    private:                
        std::string configFile;     // name of config file  (not used yet)
        std::vector<std::string> listRobotNames;
        int numJoints;
        std::vector<std::string> listJointNames;
        float modulesFreq;  // execution frequency for all modules (loops/sec)
        // joints
        ParamsJoint oJointParams[AMY_MAX_JOINTS];
        // segments
        int lenHumerus; // length of arm's humerus (cm)        
        int lenRadius; // length of arm's radius (cm)        
        // joint movers
        int brakeAccel;      // degrees/s2
        
    public:
        ArmConfig();

        // initializes the configuration for the given robot
        bool loadRobot (std::string& robotName);
        
        // checks if robot is supported
        bool checkRobotSupported(std::string& robotName);
        
        int getNumJoints() {return numJoints;};
        
        std::vector<std::string>& getListJointNames() {return listJointNames;};
        
        float getModulesFreq () {return modulesFreq;}        
        int getBrakeAccel() {return brakeAccel;}
        
        // gets the Joint module paramaters for the given joint name
        ParamsJoint& getParamsJoint(std::string jointName);
        
        int getLenHumerus() {return lenHumerus;};        
        int getLenRadius() {return lenRadius;};        

        // TEMPORAL configurations (to be removed)
        // real position not read yet. When done, return true here
        static bool isRealArmPositionRead() {return false;};
        // ArmPosition module not created yet. When created, return true here
        static bool isArmPositionModuleWorking() {return false;};
        
private:
    void loadArmVersion(ArmVersion& oArmVersion);
    void loadUR5();
    void loadYoubot();
    
};

}

#endif
