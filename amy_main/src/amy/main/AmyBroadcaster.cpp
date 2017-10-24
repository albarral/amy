/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/main/AmyBroadcaster.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AmyBroadcaster::logger(Logger::getLogger("amy.main"));

// Constructor 
AmyBroadcaster::AmyBroadcaster ()
{    
    modName = "AmyBroadcaster";
    benabled = false;
 }

void AmyBroadcaster::init(iArmInterface* pArmInterface)
{
    // prepare communications publisher
    oComyPublisher.connect();
    // prepare amy sensor informer
    oAmyComsInformer.connect2Arm(pArmInterface);
    
    // if both connected listener is enabled
    if (oComyPublisher.isConnected() && oAmyComsInformer.isConnected())
    {
        benabled = true;
    }
    else
        LOG4CXX_ERROR(logger, modName + ": failed initialization, publisher or sensor informer was not connected!");                        
};

void AmyBroadcaster::first()
{    
    log4cxx::NDC::push(modName);   	
}

void AmyBroadcaster::loop()
{
    // get arm info in form of talky message
    std::string rawMessage = oAmyComsInformer.getArmInfo();
    
    // if info obtained, broadcast it
    if (!rawMessage.empty())
        oComyPublisher.publishMessage(rawMessage);
}

}