#ifndef __AMY_ARM_TESTS_H
#define __AMY_ARM_TESTS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "amy/arm/ArmManager.h"
#include "amy/arm/bus/ArmBus.h"

namespace amy
{
// class used to conduct tests
class ArmTest
{
 private:
     static log4cxx::LoggerPtr logger;
     ArmBus* pArmBus;   // bus access
     int step;
     int direction;

public:
    ArmTest();
//    ~ArmTest();

    void connect2Bus(ArmManager& oArmManager);
    bool isConnected() {return pArmBus != 0;};
    
    void reset();            
    void newStep();
    void testKeepTilt();    

private:    
    void setPos();
    void testRacer();
    
    void testJointMove();
    void testJointControl();
    void testRadialControl();
    void testArmMath();
    void testArmPlanner();
};

}    
#endif
