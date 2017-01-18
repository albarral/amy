/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include <vector>
#include <string>
#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "amy/test/AmyCommander.h"

using namespace amy;


log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("amy.test"));

// main program
int main(int argc, char** argv) 
{
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
        
    LOG4CXX_INFO(logger, "\n\nLAUNCH amy testing ...\n");    
        
    AmyCommander oAmyCommander;
    oAmyCommander.setFrequency(5.0);
    oAmyCommander.on();
    
    while (oAmyCommander.isOn())
    {
        sleep(1);
    }
          
    oAmyCommander.wait();
    return 0;
}
