#ifndef __AMY_CORE_ROBOT_H
#define __AMY_CORE_ROBOT_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "amy/core/robot/Arm.h"

namespace amy
{
// Class to represent a robot as list of arms. 
class Robot
{
private:
    std::string name;   // arm name
    std::vector<Arm> listArms;
   
public:    
    Robot();
    ~Robot();
        
    void setName(std::string value) {name = value;};
    std::string getName() {return name;};

    // reset arms
    void reset();
    // get arms list
    std::vector<Arm>& getListArms() {return listArms;};
    // gets number of arms
    int getNumArms() {return listArms.size();};

    // checks if the robot has the given arm type
    bool hasArmType(int type);
    // get specific arm by type (assumes 2 arms at most)
    Arm* getArmByType(int type);

    // add a new arm
    void addArm(Arm& oArm);        
};
}
#endif
