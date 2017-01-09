#ifndef __AMY_CORE_AMYCONFIG_H
#define __AMY_CORE_AMYCONFIG_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include "amy/core/config/JointControlConfig.h"

namespace amy
{
class AmyConfig 
{
    private:                
        std::string usedRobot;     // name of controlled robot
        float modulesFreq;  // execution frequency for all modules (loops/sec)
        // amy arm
        std::vector<std::string> listControlledJoints;  // list of controlled joint names
        JointControlConfig oJointControlConfig;
        
    public:
        AmyConfig();
        ~AmyConfig();

        void setUsedRobot(std::string value) {this->usedRobot = value;}
        std::string getUsedRobot() {return usedRobot;}
                        
        void setModulesFreq(float value) {this->modulesFreq = value;}
        float getModulesFreq() {return modulesFreq;}

        void setListControlledJoints(std::vector<std::string>& list) {this->listControlledJoints = list;}
        std::vector<std::string>& getListControlledJoints() {return listControlledJoints;}

        void setJointControlConfig(JointControlConfig& oJointControlConfig) {this->oJointControlConfig = oJointControlConfig;}
        JointControlConfig& getJointControlConfig() {return oJointControlConfig;}

        // TEMPORAL configurations (to be removed)
        // real position not read yet. When done, return true here
        static bool isArmPositionRead() {return false;};
};

}

#endif
