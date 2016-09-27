#ifndef __AMY_JOINT_H
#define __AMY_JOINT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/arm/config/ParamsJoint.h"

namespace amy
{
// Class to represent an arm's joint. To move it use class JointMover.
class Joint
{
private:
    bool benabled;
    // configuration data
    std::string name;
    int rest;    // angle at which the joint rests (the effort is minimum)
    int length;     // joint's length (cm)
    int limit1;      // lower allowed angle (degrees)
    int limit2;      // upper allowed angle (degrees)

public:
    
    Joint();
    ~Joint();

    // initializes the joint 
    void init(ParamsJoint& oParamsJoint);        
    bool isEnabled() {return benabled;};

    std::string getName() {return name;};
    int getRestAngle() {return rest;};
    void setRestAngle(int value) {rest = value;};

    int getLowerLimit() {return limit1;}
    int getUpperLimit() {return limit2;}
};
}
#endif
