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
public: 
    static const int CYCLER1 = 1; 
    static const int CYCLER2 = 2;

private:                
        std::string usedRobot;     // name of controlled robot
        float modulesFreq;  // execution frequency for all modules (loops/sec)
        // amy arm
        std::vector<int> listControlledJoints;  // list of controlled joint types
        
    public:
        AmyConfig();
        ~AmyConfig();

        void setUsedRobot(std::string value) {usedRobot = value;}
        std::string getUsedRobot() {return usedRobot;}
                        
        void setModulesFreq(float value) {modulesFreq = value;}
        float getModulesFreq() {return modulesFreq;}

        std::vector<int>& getListControlledJoints() {return listControlledJoints;}

        // TEMPORAL configurations (to be removed)
        // real position not read yet. When done, return true here
        static bool isArmPositionRead() {return false;};
};

}

#endif
