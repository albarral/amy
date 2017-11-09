#ifndef __AMY_CORE_AMYCONFIG_H
#define __AMY_CORE_AMYCONFIG_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#define AMY_MAX_JOINTS 5

namespace amy
{
class AmyConfig 
{
    private:                
        std::string usedRobot;     // name of controlled robot
        float modulesFreq;  // execution frequency for all modules (loops/sec)
        // amy arm
        std::vector<std::string> listControlledJoints;  // list of controlled joint names
        
    public:
        AmyConfig();
        ~AmyConfig();

        void setUsedRobot(std::string value) {usedRobot = value;}
        std::string getUsedRobot() {return usedRobot;}
                        
        void setModulesFreq(float value) {modulesFreq = value;}
        float getModulesFreq() {return modulesFreq;}

        void setListControlledJoints(std::vector<std::string>& list) {listControlledJoints = list;}
        std::vector<std::string>& getListControlledJoints() {return listControlledJoints;}

        // TEMPORAL configurations (to be removed)
        // real position not read yet. When done, return true here
        static bool isArmPositionRead() {return false;};
};

}

#endif
