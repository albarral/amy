#ifndef __AMY_ARM_CONFIG_H
#define __AMY_ARM_CONFIG_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "amy/arm/config/ArmDefines.h"

namespace amy
{
class ArmConfig 
{
    private:                
        //std::string configFile;     // name of config file  (not used yet)
        std::vector<std::string> listControlledJoints;  // list of controlled joint names
        float modulesFreq;  // execution frequency for all modules (loops/sec)
        // joint movers
        int brakeAccel;      // degrees/s2
        
    public:
        ArmConfig();
        ~ArmConfig();
        
        std::vector<std::string>& getListControlledJoints() {return listControlledJoints;};
        int getNumControlledJoints() {return listControlledJoints.size();};
        
        float getModulesFreq () {return modulesFreq;}        
        int getBrakeAccel() {return brakeAccel;}
                
        // TEMPORAL configurations (to be removed)
        // real position not read yet. When done, return true here
        static bool isArmPositionRead() {return false;};
        // ArmPosition module not created yet. When created, return true here
        static bool isArmPositionModuleWorking() {return false;};    
};

}

#endif
