/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include <vector>
#include <string>
#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "amy/arm/ArmManager.h"
#include "amy/robot/SupportedRobots.h"
#include "amy/robot/Robot.h"
#include "amy/robot/Arm.h"

//#include "amy/arm/Tests.h"

using namespace amy;

void waitArmManager2End(ArmManager& oArmManager);

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("amy.arm"));

// main program
int main(int argc, char** argv) 
{
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
        
    // use UR5 (should be specified by argument)
    std::string targetRobot = SupportedRobots::UR5;

    LOG4CXX_INFO(logger, "\n\nLAUNCH amy MANIPULATION ...\n");
    LOG4CXX_INFO(logger, "target robot: " << targetRobot);

//    Tests oTests;
//    oTests.testArmMath();
//    return 0;
    
    SupportedRobots oSupportedRobots;
    Robot oRobot;
    
    // if robot not supported, skip initialization
    if (!oSupportedRobots.isRobotSupported(targetRobot))
    {
        LOG4CXX_ERROR(logger, "FAILURE!!! Robot not supported by amy.");
        return -1;        
    }
    
    // load specified robot
    if (!oSupportedRobots.loadRobotVersion(oRobot, targetRobot))
    {
        LOG4CXX_ERROR(logger, "FAILURE!!! Robot configuration could not be loaded. ");
        return -1;
    }

    int numArms = oRobot.getNumArms();
    LOG4CXX_INFO(logger, "LOADED OK, robot has " << numArms << " arm.");
        
    // amy not yet ready for multiple arms (needs multiple arm buses)
    if (numArms > 0)
    {
        if (numArms > 1)
            LOG4CXX_WARN(logger, "amy not ready for multi-arm control. Only 1 will be controlled");
            
        ArmManager oArmManager; 
        if (oArmManager.launch(oRobot, Arm::eSINGLE_ARM))
            waitArmManager2End(oArmManager);
    }
    else 
    {
        LOG4CXX_WARN(logger, "No arms. Nothing to do");
    }
      
    return 0;
}

// waits till ArmManager is asked to end
void waitArmManager2End(ArmManager& oArmManager)
{    
    std::vector<float> listPrevAngles;
    
    if (!oArmManager.isEnabled())
        return;
    
    while (!oArmManager.checkEndRequested()) 
    {
        oArmManager.readSollAngles();
        std::vector<float>& listSollAngles = oArmManager.getSollAngles();
        
        if (listSollAngles != listPrevAngles)
        {
            //LOG4CXX_INFO(logger,"moved angles: " << (int)listSollAngles.at(0) << ", " << (int)listSollAngles.at(1) << ", " << (int)listSollAngles.at(2) << ", " << (int)listSollAngles.at(3));      
            listPrevAngles = listSollAngles;            
        }

        sleep(1);
    }    

    LOG4CXX_INFO(logger, "\nend amy MANIPULATION ...\n");
    oArmManager.end();
    return;
}

