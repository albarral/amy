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
        int cruiseSpeed;  // cruise speed for the joint
        int brakeAccel;      // degrees/s2
        
    public:
        ParamsJointMover();

        void set(std::string jointName, int accel, int cruiseSpeed, int brakeAccel) {this->jointName = jointName; this->accel = accel; this->cruiseSpeed = cruiseSpeed; this->brakeAccel = brakeAccel;}

        std::string& getJointName() {return jointName;};
        int getAccel() {return accel;}
        int getCruiseSpeed() {return cruiseSpeed;}
        int getBrakeAccel() {return brakeAccel;}
};

}    
#endif
