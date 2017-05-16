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


#include "amy/arm/bus/AxisBus.h"
#include "amy/arm/move/JointAccelerator.h"
#include "amy/arm/move/JointPositioner.h"
#include "amy/arm/move/RadialPositioner.h"
#include "amy/math/ArmMath.h"
#include "amy/move/MoveFactory.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmTest::logger(Logger::getLogger("amy.arm"));    

ArmTest::ArmTest()
{
    pArmBus = 0;
}

void ArmTest::connect2Bus(ArmManager& oArmManager)
{
    pArmBus = &oArmManager.oArmBus;
}

void ArmTest::testCycler2()
{
    LOG4CXX_INFO(logger, "testCycler2");    
    
    if (!isConnected())
         return;
        
    float angle = 45; 
    float amplitude = 20;
    float freq = 0.5;
    bool bgo = true;
    pArmBus->getFrontalCyclerBus().getCO_CYCLER_ANGLE1().request(angle);
    pArmBus->getFrontalCyclerBus().getCO_CYCLER_AMPLITUDE1().request(amplitude);
    pArmBus->getFrontalCyclerBus().getCO_CYCLER_FREQ1().request(freq);
    pArmBus->getFrontalCyclerBus().getCO_CYCLER_ACTION().request(bgo);
}

void ArmTest::setPos(int pan, int tilt, int radius)
{
     if (!isConnected())
         return;

    pArmBus->getPanBus().getCO_AXIS_POS().request(pan);     
    pArmBus->getTiltBus().getCO_AXIS_POS().request(tilt);
    pArmBus->getRadialBus().getCO_AXIS_POS().request(radius);
    LOG4CXX_INFO(logger, "setPosition: " << pan << ", " << tilt << ", " << radius);
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

void ArmTest::testArmMover()
{
    LOG4CXX_INFO(logger, "testArmMover");    
    
    if (!isConnected())
         return;
        
    int movType = MoveFactory::eMOV_LINE;
    bool bgo = true;
    pArmBus->getCO_MOVER_TYPE().request(movType);
    //pArmBus->getCO_MOVER_ACTION().request(bgo);
}


}