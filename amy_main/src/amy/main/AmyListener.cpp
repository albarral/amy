/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/main/AmyListener.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AmyListener::logger(Logger::getLogger("amy.main"));

// Constructor 
AmyListener::AmyListener()
{    
    modName = "AmyListener";
    benabled = false;
 }

void AmyListener::init(iArmInterface& oArmInterface)
{
    //oAmyFileServer.connect2Arm(oArmInterface);
    oAmyZeroMQServer.connect2Arm(oArmInterface);
    benabled = true;
};

void AmyListener::first()
{    
    log4cxx::NDC::push(modName);   	
}

void AmyListener::loop()
{
    // listen to user commands
    /*if (oAmyFileServer.readCommand())
    {
        if (oAmyFileServer.isValid())
        {
            oAmyFileServer.processCommand();
        }
        else
            LOG4CXX_WARN(logger, "invalid command");                                      
    }*/
        if (oAmyZeroMQServer.readCommand())
    {
        if (oAmyZeroMQServer.isValid())
        {
            oAmyZeroMQServer.processCommand();
        }
        else
            LOG4CXX_WARN(logger, "invalid command");                                      
    }
}

bool AmyListener::checkAmyEndRequested()
{
    //return oAmyFileServer.isAmyEndRequested();   
    return oAmyZeroMQServer.isAmyEndRequested(); 
}
}