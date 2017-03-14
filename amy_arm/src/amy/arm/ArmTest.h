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

public:
    ArmTest();
//    ~ArmTest();

    void connect2Bus(ArmManager& oArmManager);
    bool isConnected() {return pArmBus != 0;};
    
    void setPos(int pan, int tilt, int radius);
    void testCycler();
    void testKeepTilt();    

private:        
    void testJointMove();
    void testJointControl();
    void testRadialControl();
    void testArmMath();
};

}    
#endif
