/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/config/ArmConfig.h"
#include "amy/arm/config/versions/ArmUR5.h"
#include "amy/arm/config/versions/ArmYoubot.h"

namespace amy
{
const std::string ArmConfig::horizontal_shoulder = "hs";
const std::string ArmConfig::vertical_shoulder = "vs";
const std::string ArmConfig::elbow = "el";
const std::string ArmConfig::horizontal_wrist = "hw";
const std::string ArmConfig::vertical_wrist = "vw";
    
// Constructor
ArmConfig::ArmConfig ()
{    
    // TEMPORAL: all params should be read from a file    
    modulesFreq = 5;  // 5 Hz
    brakeAccel = 30;
    
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
    
    return true;
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

void ArmConfig::loadArmVersion(ArmVersion& oArmVersion)
{    
    int i=0;
    std::string jointName;
    
    if (oArmVersion.hasHS())
    {
        jointName = ArmConfig::horizontal_shoulder;
        oJointParams[i].set(jointName, oArmVersion.getHSlower(), oArmVersion.getHSupper());
        listJointNames.push_back(jointName);
    }

    if (oArmVersion.hasVS())
    {
        i++;
        jointName = ArmConfig::vertical_shoulder;
        oJointParams[i].set(jointName, oArmVersion.getVSlower(), oArmVersion.getVSupper());
        listJointNames.push_back(jointName);
    }


    if (oArmVersion.hasEL())
    {
        i++;
        jointName = ArmConfig::elbow;
        oJointParams[i].set(jointName, oArmVersion.getELlower(), oArmVersion.getELupper());
        listJointNames.push_back(jointName);
    }

    if (oArmVersion.hasHW())
    {
        i++;
        jointName = ArmConfig::horizontal_wrist;
        oJointParams[i].set(jointName, oArmVersion.getHWlower(), oArmVersion.getHWupper());
        listJointNames.push_back(jointName);
    }
        
    if (oArmVersion.hasVW())
    {
        i++;
        jointName = ArmConfig::vertical_wrist;
        oJointParams[i].set(jointName, oArmVersion.getVWlower(), oArmVersion.getVWupper());
        listJointNames.push_back(jointName);
    }

    lenHumerus = oArmVersion.getLenHumerus();
    lenRadius = oArmVersion.getLenRadius();
    
    numJoints = listJointNames.size();
}

// return short alias for each joint
//std::string ArmConfig::getAlias4Joint(std::string jointName)
//{
//    if (jointName.compare(ArmConfig::horizontal_shoulder) == 0)
//        return "HS";
//    else if (jointName.compare(ArmConfig::vertical_shoulder) == 0)
//        return "VS";
//    else if (jointName.compare(ArmConfig::elbow) == 0)
//        return "EL";
//    else if (jointName.compare(ArmConfig::horizontal_wrist) == 0)
//        return "HW";
//    else if (jointName.compare(ArmConfig::vertical_wrist) == 0)
//        return "VW";
//    else 
//        return "UNDEF";           
//}


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

