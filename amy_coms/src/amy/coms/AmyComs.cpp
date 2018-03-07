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
     
    // launch server module
    oArmServer.init(oArmBus);
    oArmServer.setFrequency(freq);
    oArmServer.on();

    // launch publisher module
    oArmPublisher.init(oArmBus);
    oArmPublisher.setFrequency(freq);
    oArmPublisher.on();
    
    return true;
}

bool AmyComs::end()
{
    LOG4CXX_INFO(logger, "AmyComs: end modules");

    // finish server module
    oArmServer.off();
    oArmServer.wait();      
    
    // finish publisher module
    oArmPublisher.off();
    oArmPublisher.wait();      

    return true;
}

bool AmyComs::checkAmyEndRequested()
{
    return oArmServer.getAmyEndRequested();
}

}		
