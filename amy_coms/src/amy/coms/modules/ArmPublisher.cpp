/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/coms/modules/ArmPublisher.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmPublisher::logger(Logger::getLogger("amy.coms"));

// Constructor 
ArmPublisher::ArmPublisher ()
{    
    modName = "ArmPublisher";
    benabled = false;
 }

void ArmPublisher::init(ArmBus& oArmBus)
{
    // prepare communication publishers
    oJointChannelPublisher.connect2Bus(oArmBus);
    oAxisChannelPublisher.connect2Bus(oArmBus);
    
    // if publishers enabled
    if (oJointChannelPublisher.isTuned() &&     
        oAxisChannelPublisher.isTuned())
    {
        benabled = true;
        LOG4CXX_INFO(logger, modName + " initialized");                                
    }
    else
        LOG4CXX_ERROR(logger, modName + ": failed initialization, channel publishers not tuned!");                        
}

void ArmPublisher::first()
{    
    log4cxx::NDC::push(modName);   	
}

void ArmPublisher::loop()
{      
    // sense channels data
    oJointChannelPublisher.senseData();
    oAxisChannelPublisher.senseData();
    
    // publish channels data
    oJointChannelPublisher.sendData();
    oAxisChannelPublisher.sendData();
}

}