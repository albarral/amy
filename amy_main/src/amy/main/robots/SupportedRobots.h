#ifndef __AMY_MAIN_SUPPORTED_ROBOTS_H
#define __AMY_MAIN_SUPPORTED_ROBOTS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "amy/core/robot/Robot.h"

namespace amy
{
// Class to represent a robot as list of arms. 
class SupportedRobots
{
public:
    static const std::string UR5;   // Universal Robotss UR5    
    static const std::string Youbot;    // Kuka Youbot
    
private:
    std::vector<std::string> listSupportedRobots;
   
public:    
    SupportedRobots();
    ~SupportedRobots();
        
    // checks if robot is supported
    bool isRobotSupported(std::string version);
    
    // load robot version
    bool loadRobotVersion(Robot& oRobot, std::string version);

};
}
#endif
