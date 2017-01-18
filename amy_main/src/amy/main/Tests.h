#ifndef __AMY_MAIN_TESTS_H
#define __AMY_MAIN_TESTS_H

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
class Tests
{
 private:
     static log4cxx::LoggerPtr logger;

public:
//    Tests();
//    ~Tests();

    void testFileReader(std::string name);
    void testFileWriter();    
    void testAmyServer();
    void testAmyPublisher();
};

}    
#endif
