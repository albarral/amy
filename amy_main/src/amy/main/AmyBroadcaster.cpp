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
    pArmInterface = 0;
 }

void AmyBroadcaster::init(iArmInterface& oArmInterface)
{
    // access arm interface
    pArmInterface = &oArmInterface;
    // and init the publisher
    oAmyPublisher.init();
    if (oAmyPublisher.isEnabled())
    {
        benabled = true;
        LOG4CXX_INFO(logger, modName << " initialized");          
    }
    else    
        LOG4CXX_ERROR(logger, modName << " init failed");                  
};

void AmyBroadcaster::first()
{    
    log4cxx::NDC::push(modName);   	
}

void AmyBroadcaster::loop()
{        
    fetchInfo();

    // if control values have changed, broadcast them 
    if (!oArmData.sameSollValues(oArmData0))
    {
        oAmyPublisher.publishArmControl(oArmData);
        // and store them for next comparison
        oArmData0 = oArmData;        
    }
}

void AmyBroadcaster::fetchInfo()
{        
    // read commanded control values of all joints
    oArmData.setSollHS(pArmInterface->getHSControl());
    oArmData.setSollVS(pArmInterface->getVSControl());
    oArmData.setSollEL(pArmInterface->getELControl());
    oArmData.setSollHW(pArmInterface->getHWControl());
    oArmData.setSollVW(pArmInterface->getVWControl());   
}

}