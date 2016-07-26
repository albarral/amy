#ifndef __SAM_MANIPULATION_CONFIG_H
#define __SAM_MANIPULATION_CONFIG_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "amy/arm/config/defines.h"
#include "amy/arm/config/ParamsJoint.h"
#include "amy/arm/config/ParamsJointMover.h"

namespace amy
{
class ArmConfig 
{
public:
    static const std::string horizontal_shoulder;
    static const std::string vertical_shoulder;
    static const std::string elbow;
    static const std::string vertical_wrist;
    
    private:                
        std::string configFile;     // name of config file  (not used yet)
        std::vector<std::string> listRobotNames;
        int numJoints;
        std::vector<std::string> listJointNames;
        float modulesFreq;  // execution frequency for all modules (loops/sec)
        // joints
        ParamsJoint oJointParams[SAM_MAX_JOINTS];
        // joint movers
        ParamsJointMover oJointMoverParams[SAM_MAX_JOINTS];
        
    public:
        ArmConfig();

        // initializes the configuration for the given robot
        bool loadRobot (std::string& robotName);
        
        // checks if robot is supported
        bool checkRobotSupported(std::string& robotName);
        
        int getNumJoints() {return numJoints;};
        
        std::vector<std::string>& getListJointNames() {return listJointNames;};
        
        float getModulesFreq () {return modulesFreq;}        
        
        // gets the Joint module paramaters for the given joint name
        ParamsJoint& getParamsJoint(std::string jointName);
        // gets the JointMover module paramaters for the given joint name
        ParamsJointMover& getParamsJointMover(std::string jointName);
        
private:
    void loadYoubot();
    void loadUR5();
    // void loadOwi();
};

}

#endif
