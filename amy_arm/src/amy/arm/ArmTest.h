#ifndef __AMY_ARM_TESTS_H
#define __AMY_ARM_TESTS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>


namespace amy
{
// class used to conduct tests
class ArmTest
{
 private:
     static log4cxx::LoggerPtr logger;

public:
//    Tests();
//    ~Tests();

    void testJointMover();
    void testJointDriver();
    void testRadialDriver();
    void testArmMath();
    void testArmPlanner();
};

}    
#endif
