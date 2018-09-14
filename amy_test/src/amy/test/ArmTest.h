#ifndef __AMY_TEST_ARMTEST_H
#define __AMY_TEST_ARMTEST_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

namespace amy
{
// class used to conduct tests
class ArmTest
{
 private:
     static log4cxx::LoggerPtr logger;

public:
    ArmTest();
//    ~ArmTest();
    
    void testJointPos();
    void testAxesPos(int pan, int tilt, int radius);
    void testAxesSpeed(int vpan, int vtilt, int vradius);
    void testCycler();
    
    void testJointAccelerator();
    void testJointPositioner();
    void testRadialPositioner();
    
};

}    
#endif
