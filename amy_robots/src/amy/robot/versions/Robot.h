#ifndef __AMY_ROBOT_ARM_H
#define __AMY_ROBOT_ARM_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "amy/robot/Arm.h"

namespace amy
{
// Class to represent a robot as list of arms. 
class Robot
{
public:
    static const std::string left_arm;
    static const std::string right_arm;
    
private:
    std::string name;   // arm name
    std::vector<Arm> listArms;
    std::vector<std::string> listSupportedRobots;
   
public:    
    Robot();
    ~Robot();
        
    void setName(std::string value) {name = value;};
    std::string getName() {return name;};

    // checks if robot is supported
    bool checkVersionSupported(std::string version);
    // load robot version
    bool loadVersion(std::string version);

    // reset arms
    void reset();
    // get arms list
    std::vector<Arm>& getListArms() {return listArms;};
    // gets number of arms
    int getNumArms() {return listArms.size();};

protected:
    // add a new arm
    void addArm(Arm& oArm);
    
    
};
}
#endif
