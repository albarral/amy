/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <string>
#include <unistd.h> // for sleep() 
#include <cstdlib>  // for getenv
#include <fstream>
#include <cmath>

#include <log4cxx/logger.h>

#include "amy/arm/ArmTest.h"


#include "amy/arm/move/JointAccelerator.h"
#include "amy/arm/move/JointPositioner.h"
#include "amy/arm/move/RadialPositioner.h"
#include "amy/arm/move/ArmMath.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmTest::logger(Logger::getLogger("amy.arm"));    

ArmTest::ArmTest()
{
    pArmBus = 0;
    reset();
}

void ArmTest::connect2Bus(ArmManager& oArmManager)
{
    pArmBus = &oArmManager.oArmBus;
}

void ArmTest::reset()
{
    step = 0; 
    direction = 1;    
}

void ArmTest::newStep()
{
    step++;

    LOG4CXX_INFO(logger, "step " << step);    
    
     if (step <= 5)
         setPos();
     else
         testRacer();            
}

void ArmTest::setPos()
{
    int value;

     if (!isConnected())
         return;
     
    switch (step)
    {
        case 1: 
            value = -60;
            pArmBus->getCO_ARM_PAN().request(value);            
            LOG4CXX_INFO(logger, "initialPosition: pan");
            break;
            
        case 3: 
            value = 80;
            pArmBus->getCO_ARM_TILT().request(value);
            LOG4CXX_INFO(logger, "initialPosition: tilt");
            break;

        case 5: 
            value = 60;
            pArmBus->getCO_ARM_RADIUS().request(value);            
            LOG4CXX_INFO(logger, "initialPosition: radius");
            break;
    }    
}


void ArmTest::testRacer()
{
    if (!isConnected())    
        return;

    float speed = 40.0;
    switch (step)
    {
        case 7: 
              pArmBus->getCO_PAN_SPEED().request(speed);
            break;
            
        case 9: 
              pArmBus->getCO_TILT_SPEED().request(-speed);
            break;

        case 1: 
              pArmBus->getCO_PAN_SPEED().request(0);
              pArmBus->getCO_TILT_SPEED().request(0);
            break;
    }    
    
    
    // change pan direction every 2 steps
//    bool beven = (fmod(step, 2) == 0.0);
//    if (beven)
//    {
//        direction = -direction;
//        float speed = direction*80.0;
//        oArmManager.oArmBus.getCO_PAN_SPEED(speed);
//    }
}

void ArmTest::testKeepTilt()
{
    LOG4CXX_INFO(logger, "testKeepTilt");

    if (!isConnected())    
        return;

    bool keep = true;
    pArmBus->getCO_KEEP_TILT().request(keep);
}

void ArmTest::testJointMove()
{
    JointAccelerator oMover;
  
    LOG4CXX_INFO(logger, "\nNew test JointMove ...\n");
    
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

void ArmTest::testJointControl()
{
    JointAccelerator oMover;
    JointPositioner oDriver;
    float angle, accel;
  
    LOG4CXX_INFO(logger, "\nNew test JointControl ...\n");
    
    oDriver.init(4.0, 2.0, 0.05, 60.0);
    
    oDriver.setNewMove(180.0);    
    while (oDriver.getState() != JointPositioner::eSTATE_DONE)
    {
        angle = oMover.getAngle();
        accel = oDriver.drive(angle);
        oMover.move(accel, angle);
        LOG4CXX_INFO(logger, oDriver.toString() << "\n");
        LOG4CXX_INFO(logger, oMover.toString() << "\n");
        usleep(100000);
    }    
}

void ArmTest::testRadialControl()
{
    JointAccelerator oMover;
    RadialPositioner oDriver;
    float angle, accel;
  
    LOG4CXX_INFO(logger, "\nNew test RadialControl ...\n");
    
    oDriver.init(4.0, 2.0, 0.05, 60.0);
    oDriver.setArmSize(40, 40);
    
    oDriver.newRadialMove(40);
    while (oDriver.getState() != JointPositioner::eSTATE_DONE)
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
        tilt = oArmMath.computeTilt4JointAngles(angleVS, angleEL);
        radius = oArmMath.computeRadius4ElbowAngle(angleEL);
        LOG4CXX_INFO(logger, "angleVS: " << angleVS << ", angleEL: " << angleEL << ", radius= " << radius << ", tilt= " << tilt << "\n");
        angleVS -= 30;
    }

//    radius = 40;
//    float angle = oArmMath.calcElbowAngle(radius);
//    LOG4CXX_INFO(logger, "radius: " << radius << ", angle = " << angle << "\n");
}



}