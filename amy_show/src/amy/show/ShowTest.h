#ifndef __AMY_SHOW_TEST_H
#define __AMY_SHOW_TEST_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

namespace amy
{
// class used to conduct tests
class ShowTest
{
 private:
     static log4cxx::LoggerPtr logger;

public:
//    ShowTest();
//    ~ShowTest();

    void testArmPlot();
    void testHistoryPlot();
    void testDiscPlot();
    
};

}    
#endif
