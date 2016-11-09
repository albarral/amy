/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <stddef.h>

#include "amy/robot/Robot.h"
#include "amy/robot/versions/ArmUR5.h"
#include "amy/robot/versions/ArmYoubot.h"

namespace amy
{
const std::string Robot::left_arm = "leftArm";
const std::string Robot::right_arm = "rightArm";
    
Robot::Robot ()
{
    name = "robot";
  
    listSupportedRobots.push_back("Youbot");    // Kuka Youbot
    listSupportedRobots.push_back("UR5");        // Universal Robots UR5    
}

Robot::~Robot()
{
    reset();
}

void Robot::reset()
{
    listArms.clear();    
}

void Robot::addArm(Arm& oArm)
{
    listArms.push_back(oArm);    
}

bool Robot::loadVersion(std::string version)
{
    
    
}

bool ArmConfig::loadRobot (std::string& robotName)
{
    if (!checkRobotSupported(robotName))
        return false;
        
    if (robotName.compare("Youbot") == 0) 
        loadYoubot();
    else if (robotName.compare("UR5") == 0) 
        loadUR5();
    
    return true;
}

bool Robot::checkVersionSupported(std::string version)
{
    bool bfound = false;
    // walk the list to find the name
    for (std::string& robotName : listSupportedRobots)
    {
        if (version.compare(robotName) == 0) 
        {
            bfound = true;
            break;
        }
    }        
    return bfound;
}

}
