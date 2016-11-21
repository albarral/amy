#ifndef __AMY_ARM_TESTS_H
#define __AMY_ARM_TESTS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "amy/network/ArmNetwork.h"

namespace amy
{
// class used to conduct tests
class Tests
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
    void testAmyNetwork2();

private:        
    void writePos(ArmNetwork& oArmNetwork, int value);
    void readPos(ArmNetwork& oArmNetwork);
};

}    
#endif
