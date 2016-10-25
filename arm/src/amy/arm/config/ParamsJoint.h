#ifndef __AMY_ARM_PARAMSJOINT_H
#define __AMY_ARM_PARAMSJOINT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace amy
{
// Config params for Joint class
class ParamsJoint 
{
   private:                
        std::string jointName;
        int limit1; // lower limit (degrees)
        int limit2; // upper limit (degrees)
        
    public:
        ParamsJoint();

        void set(std::string jointName, int limit1, int limit2) {this->jointName = jointName; this->limit1 = limit1; this->limit2 = limit2;};

        std::string& getJointName() {return jointName;};
        int getLimit1() {return limit1;};
        int getLimit2() {return limit2;};
};

}    
#endif
