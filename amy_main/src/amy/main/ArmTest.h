#ifndef __AMY_MAIN_ARMTEST_H
#define __AMY_MAIN_ARMTEST_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "amy/core/bus/ArmBus.h"

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

    void connect2Bus(ArmBus& oArmBus);
    bool isConnected() {return pArmBus != 0;};
    
    void setPos(int pan, int tilt, int radius);
    void testCycler2();
    void testKeepTilt();    

    void testComs();
    void testComsReception();

private:        
    void testJointMove();
    void testJointControl();
    void testRadialControl();
    
};

}    
#endif
