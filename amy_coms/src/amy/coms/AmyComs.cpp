/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics  *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/AmyComs.h"

namespace amy
{
log4cxx::LoggerPtr AmyComs::logger(log4cxx::Logger::getLogger("amy.coms"));

AmyComs::AmyComs() 
{
}

AmyComs::~AmyComs()
{    
}
     
 bool AmyComs::launch(ArmBus& oArmBus)
{
    LOG4CXX_INFO(logger, "AmyComs: launch modules");
    float freq = oAmyConfig.getModulesFreq();
     
    // launch listener module
    oAmyListener.init(oArmBus);
    oAmyListener.setFrequency(freq);
    oAmyListener.on();

    // launch broadcaster module
    oAmyBroadcaster.init(oArmBus);
    oAmyBroadcaster.setFrequency(freq);
    oAmyBroadcaster.on();
    
    return true;
}

bool AmyComs::end()
{
    LOG4CXX_INFO(logger, "AmyComs: end modules");

    // finish listener module
    oAmyListener.off();
    oAmyListener.wait();      
    
    // finish broadcaster module
    oAmyBroadcaster.off();
    oAmyBroadcaster.wait();      

    return true;
}

bool AmyComs::checkAmyEndRequested()
{
    return oAmyListener.getAmyEndRequested();
}

}		
