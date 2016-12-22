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
    bconnected = false;
    pArmBus = 0;
 }

void AmyListener::connect(ArmBus* pArmBus)
{
    this->pArmBus = pArmBus;    
    oAmyFileServer.connect(pArmBus);
    bconnected = true;
};

void AmyListener::first()
{    
    log4cxx::NDC::push(modName);   	
}

void AmyListener::loop()
{
    // listen to user commands
    if (oAmyFileServer.readCommand())
    {
        if (oAmyFileServer.isValid())
        {
            oAmyFileServer.processCommand();
        }
        else
            LOG4CXX_WARN(logger, "invalid command");                                      
    }
    else
        LOG4CXX_WARN(logger, "no command");                                      
}

}