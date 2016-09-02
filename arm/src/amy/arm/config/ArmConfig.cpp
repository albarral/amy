/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/config/ArmConfig.h"
#include "amy/arm/config/versions/ArmUR5.h"
#include "amy/arm/config/versions/ArmYoubot.h"

namespace amy
{
const std::string ArmConfig::horizontal_shoulder = "hshoulder";
const std::string ArmConfig::vertical_shoulder = "vshoulder";
const std::string ArmConfig::elbow = "elbow";
const std::string ArmConfig::horizontal_wrist = "hwrist";
const std::string ArmConfig::vertical_wrist = "vwrist";
    
// Constructor
ArmConfig::ArmConfig ()
{    
    // TEMPORAL: all params should be read from a file    
    modulesFreq = 5;  // 5 Hz
    
    listRobotNames.push_back("Youbot");    // Kuka Youbot
    listRobotNames.push_back("UR5");        // Universal Robots UR5    
}


bool ArmConfig::loadRobot (std::string& robotName)
{
    if (!checkRobotSupported(robotName))
        return false;
        
    if (robotName.compare("Youbot") == 0) 
        loadYoubot();
    else if (robotName.compare("UR5") == 0) 
        loadUR5();
}

bool ArmConfig::checkRobotSupported(std::string& robotName)
{
    bool bfound = false;
    // walk the list to find the name
    std::vector<std::string>::iterator it_name = listRobotNames.begin();

    while (it_name != listRobotNames.end())
    {
        if (robotName.compare(*it_name) == 0) 
        {
            bfound = true;
            break;
        }
        it_name++;
    }        
    return bfound;
}

ParamsJoint& ArmConfig::getParamsJoint(std::string jointName)
{
    for (int i=0; i<numJoints; i++)
    {
        if (oJointParams[i].getJointName().compare(jointName) == 0)          
            return oJointParams[i];
    }
      
    // temporal: if not found return the first (should use lists)
    return oJointParams[0];    
}

ParamsJointMover& ArmConfig::getParamsJointMover(std::string jointName)
{
    for (int i=0; i<numJoints; i++)
    {
        if (oJointMoverParams[i].getJointName().compare(jointName) == 0)                
            return oJointMoverParams[i];
    }

    // temporal: if not found return the first (should use lists)
    return oJointMoverParams[0];        
}


void ArmConfig::loadArmVersion(ArmVersion& oArmVersion)
{    
    int accel = 15;
    int brakeAccel = 30;
    int maxSpeed = 40;
    int i=0;
    
    if (oArmVersion.hasHS())
    {
        std::string hshoulder = ArmConfig::horizontal_shoulder;
        oJointParams[i].set(hshoulder, oArmVersion.getHSlower(), oArmVersion.getHSupper(), oArmVersion.getLen());
        oJointMoverParams[i].set(hshoulder, accel, maxSpeed, brakeAccel);        
        listJointNames.push_back(hshoulder);
    }

    if (oArmVersion.hasVS())
    {
        i++;
        std::string vshoulder = ArmConfig::vertical_shoulder;
        oJointParams[i].set(vshoulder, oArmVersion.getVSlower(), oArmVersion.getVSupper(), oArmVersion.getLen());
        oJointMoverParams[i].set(vshoulder, accel, maxSpeed, brakeAccel);
        listJointNames.push_back(vshoulder);
    }


    if (oArmVersion.hasEL())
    {
        i++;
        std::string elbow = ArmConfig::elbow;
        oJointParams[i].set(elbow, oArmVersion.getELlower(), oArmVersion.getELupper(), oArmVersion.getLen());
        oJointMoverParams[i].set(elbow, accel, maxSpeed, brakeAccel);
        listJointNames.push_back(elbow);
    }

    if (oArmVersion.hasHW())
    {
        i++;
        std::string hwrist = ArmConfig::horizontal_wrist;
        oJointParams[i].set(hwrist, oArmVersion.getHWlower(), oArmVersion.getHWupper(), oArmVersion.getLen());
        oJointMoverParams[i].set(hwrist, accel, maxSpeed, brakeAccel);
        listJointNames.push_back(hwrist);
    }
        
    if (oArmVersion.hasVW())
    {
        i++;
        std::string vwrist = ArmConfig::vertical_wrist;
        oJointParams[i].set(vwrist, oArmVersion.getVWlower(), oArmVersion.getVWupper(), oArmVersion.getLen());
        oJointMoverParams[i].set(vwrist, accel, maxSpeed, brakeAccel);
        listJointNames.push_back(vwrist);
    }

    numJoints = listJointNames.size();
}

void ArmConfig::loadUR5()
{    
    ArmUR5 oArmUR5;
    loadArmVersion(oArmUR5);
}

void ArmConfig::loadYoubot()
{    
    ArmYoubot oArmYoubot;
    loadArmVersion(oArmYoubot);
}

}

