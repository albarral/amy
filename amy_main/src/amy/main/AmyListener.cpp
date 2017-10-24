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

void AmyListener::init(iArmInterface* pArmInterface)
{
    // prepare communications server
    oComyServer.connect();
    // prepare amy control server
    oAmyComsServer.connect2Arm(pArmInterface);
    
    // if both connected listener is enabled
    if (oComyServer.isConnected() && oAmyComsServer.isConnected())
    {
        benabled = true;
    }
    else
        LOG4CXX_ERROR(logger, modName + ": failed initialization, coms or control server was not connected!");                        
}

void AmyListener::first()
{    
    log4cxx::NDC::push(modName);   	
}

void AmyListener::loop()
{
    // listen to received messages
    if (oComyServer.readMessage())
    {
        LOG4CXX_INFO(logger, modName + ": msg received - " + oComyServer.getRawMessage());        
        // if something received process it
        oAmyComsServer.processMessage(oComyServer.getRawMessage());
    }            
}

bool AmyListener::checkAmyEndRequested()
{
    return oAmyComsServer.isAmyEndRequested();    
}
}