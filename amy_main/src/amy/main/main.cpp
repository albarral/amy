/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include <vector>
#include <string>
#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "amy/main/AmyControl.h"
#include "amy/main/robots/SupportedRobots.h"
#include "amy/core/robot/Robot.h"

#include "amy/main/Tests.h"

using namespace amy;

// starts the amy control for the specified robot
void startAmy(Robot& oRobot);

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("amy"));

// main program
int main(int argc, char** argv) 
{
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
        
    // use UR5 (should be specified by argument)
    std::string targetRobot = SupportedRobots::UR5;

    LOG4CXX_INFO(logger, "\n\nSTART amy\n");
    LOG4CXX_INFO(logger, "target robot: " << targetRobot);

//    Tests oTests;
//    oTests.testAmyPublisher();
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
        
    if (numArms > 0)
    {
        // amy not ready for multiple arms yet
        if (numArms == 1)
            startAmy(oRobot);
        else              
            LOG4CXX_WARN(logger, "amy not ready for multi-arm control. Only 1 will be controlled");
            
    }
    else 
        LOG4CXX_WARN(logger, "No arms. Nothing to do");
      
    return 0;
}

// starts the amy control for the specified robot
void startAmy(Robot& oRobot)
{        
    AmyControl oAmyControl; 

    // launch amy control & wait for it to end        
    if (oAmyControl.launch(oRobot))
    {
        while (!oAmyControl.checkEndRequested()) 
        {
            sleep(1);
        }    

        LOG4CXX_INFO(logger, "\namy end requested ...\n");
        oAmyControl.end();        
    }
    else
        LOG4CXX_ERROR(logger, "AmyControl could not be launched");
        
    return;
}
