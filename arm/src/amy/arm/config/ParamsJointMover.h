#ifndef __AMY_ARM_PARAMSJOINTMOVER_H
#define __AMY_ARM_PARAMSJOINTMOVER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace amy
{
// Config params for JointMover modules
class ParamsJointMover 
{
    private:                
        std::string jointName;
        int accel;          // degrees/s2
        int maxSpeed;  // maximum speed allowed for the joint
        int brakeAccel;      // degrees/s2
        
    public:
        ParamsJointMover();

        void set(std::string jointName, int accel, int maxSpeed, int brakeAccel) {this->jointName = jointName; this->accel = accel; this->maxSpeed = maxSpeed; this->brakeAccel = brakeAccel;}

        std::string& getJointName() {return jointName;};
        int getAccel() {return accel;}
        int getMaxSpeed() {return maxSpeed;}
        int getBrakeAccel() {return brakeAccel;}
};

}    
#endif
