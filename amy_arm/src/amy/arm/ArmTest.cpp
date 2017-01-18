/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <string>
#include <unistd.h> // for sleep() 
#include <cstdlib>  // for getenv
#include <fstream>

#include <log4cxx/logger.h>

#include "amy/arm/ArmTest.h"

// test arm planner
#include "amy/arm/modules/ArmComputer.h"
#include "amy/arm/data/MoveStep.h"
#include "amy/arm/move/JointMover.h"
#include "amy/arm/move/JointDriver.h"
#include "amy/arm/move/RadialDriver.h"
#include "amy/arm/move/ArmMath.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmTest::logger(Logger::getLogger("amy.arm"));    

void ArmTest::testJointMover()
{
    JointMover oMover;
  
    LOG4CXX_INFO(logger, "\nNew test JointMover ...\n");
    
    float accel = 10.0;
    float angle = oMover.getAngle();
    for (int i=0; i<5; i++)
    {
        angle = oMover.getAngle();
        accel += 10;
        oMover.move(accel, angle);
        LOG4CXX_INFO(logger, oMover.toString() << "\n");
        sleep(1);
    }    
}

void ArmTest::testJointDriver()
{
    JointMover oMover;
    JointDriver oDriver;
    float angle, accel;
  
    LOG4CXX_INFO(logger, "\nNew test JointDriver ...\n");
    
    oDriver.init(4.0, 2.0, 0.05, 60.0);
    
    oDriver.setTarget(180.0);    
    while (oDriver.getState() != JointDriver::eSTATE_DONE)
    {
        angle = oMover.getAngle();
        accel = oDriver.drive(angle);
        oMover.move(accel, angle);
        LOG4CXX_INFO(logger, oDriver.toString() << "\n");
        LOG4CXX_INFO(logger, oMover.toString() << "\n");
        usleep(100000);
    }    
}

void ArmTest::testRadialDriver()
{
    JointMover oMover;
    RadialDriver oDriver;
    float angle, accel;
  
    LOG4CXX_INFO(logger, "\nNew test RadialDriver ...\n");
    
    oDriver.init(4.0, 2.0, 0.05, 60.0);
    oDriver.setArmSize(40, 40);
    
    oDriver.setTargetRadius(40);
    while (oDriver.getState() != JointDriver::eSTATE_DONE)
    {
        angle = oMover.getAngle();
        accel = oDriver.drive(angle);
        oMover.move(accel, angle);
        LOG4CXX_INFO(logger, oDriver.toString() << "\n");
        LOG4CXX_INFO(logger, oMover.toString() << "\n");
        usleep(100000);
    }    
}

void ArmTest::testArmMath()
{
    ArmMath oArmMath;
    oArmMath.setLengths(20,80);
    
    float tilt, radius;
    float angleVS, angleEL;

    angleVS = 90; 
    angleEL = -160;
    
    for (int i=0; i<4; i++)
    {
        tilt = oArmMath.convJoints2ArmTilt(angleVS, angleEL);
        radius = oArmMath.convJoints2ArmRadius(angleEL);
        LOG4CXX_INFO(logger, "angleVS: " << angleVS << ", angleEL: " << angleEL << ", radius= " << radius << ", tilt= " << tilt << "\n");
        angleVS -= 30;
    }

//    radius = 40;
//    float angle = oArmMath.calcElbowAngle(radius);
//    LOG4CXX_INFO(logger, "radius: " << radius << ", angle = " << angle << "\n");
}

void ArmTest::testArmPlanner()
{
    Movement oMovement;
    int maxSpeed = 40;    
    
    MoveStep oStep1(30, 5000, maxSpeed);
    MoveStep oStep2(45, 5000, maxSpeed);
    MoveStep oStep3(60, 5000, maxSpeed);
    MoveStep oStep4(89, 5000, maxSpeed);
    
    ArmComputer::computeMoveStep(oStep1);
    ArmComputer::computeMoveStep(oStep2);
    ArmComputer::computeMoveStep(oStep3);
    ArmComputer::computeMoveStep(oStep4);
    
    LOG4CXX_INFO(logger, "step1: " << oStep1.getDescription());
    LOG4CXX_INFO(logger, "step2: " << oStep2.getDescription());
    LOG4CXX_INFO(logger, "step3: " << oStep3.getDescription());
    LOG4CXX_INFO(logger, "step4: " << oStep4.getDescription());
}
    

}