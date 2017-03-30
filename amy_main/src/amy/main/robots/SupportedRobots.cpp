/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/main/robots/SupportedRobots.h"
#include "amy/main/robots/ArmUR5.h"
#include "amy/main/robots/ArmYoubot.h"

namespace amy
{
const std::string SupportedRobots::UR5 = "UR5";
const std::string SupportedRobots::Youbot = "youBot";
    
SupportedRobots::SupportedRobots ()
{
    // fill list of supported robots
    listSupportedRobots.push_back(SupportedRobots::UR5);    
    listSupportedRobots.push_back(SupportedRobots::Youbot);       
}

SupportedRobots::~SupportedRobots()
{
    listSupportedRobots.clear();
}

bool SupportedRobots::isRobotSupported(std::string version)
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

bool SupportedRobots::loadRobotVersion (Robot& oRobot, std::string version)
{
    if (!isRobotSupported(version))
        return false;
    
    // first reset the robot    
    oRobot.reset();
    
    // then add an appropriate arm version
    if (version.compare(SupportedRobots::Youbot) == 0) 
    {
        // Youbot has a single arm
        ArmYoubot oArmYoubot;
        oArmYoubot.setType(Arm::eSINGLE_ARM);
        oRobot.addArm(oArmYoubot);
        oRobot.setName(SupportedRobots::Youbot);
    }
    else if (version.compare(SupportedRobots::UR5) == 0) 
    {
        // UR5 is a single arm
        ArmUR5 oArmUR5;
        oArmUR5.setType(Arm::eSINGLE_ARM);
        oRobot.addArm(oArmUR5);
        oRobot.setName(SupportedRobots::UR5);
    }
    
    return true;
}

}
