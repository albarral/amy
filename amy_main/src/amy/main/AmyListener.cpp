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
    oAmyFileServer.connect2Arm(oArmInterface);
    benabled = true;
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
        // if something received, interpret it and process it
        std::string text = oAmyFileServer.getText();
        oAmyFileServer.processCommand(text);
    }
}

bool AmyListener::checkAmyEndRequested()
{
    return oAmyFileServer.isAmyEndRequested();    
}
}