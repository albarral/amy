/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/coms/modules/AmyBroadcaster.h"
#include "talky/Topics.h"
#include "talky/topics/ArmTopic.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AmyBroadcaster::logger(Logger::getLogger("amy.coms"));

// Constructor 
AmyBroadcaster::AmyBroadcaster ()
{    
    modName = "AmyBroadcaster";
    benabled = false;
 }

void AmyBroadcaster::init(ArmBus& oArmBus)
{
    int topic = talky::Topics::eTOPIC_ARM;

    // prepare communication publishers
    oNetyPublisherJoints.init(topic, talky::ArmTopic::eCAT_ARM_JOINT);
    oNetyPublisherAxis.init(topic, talky::ArmTopic::eCAT_ARM_AXIS);
    
    // prepare amy sensor informer
    oComsOutArmSense.connect2Arm(oArmBus);
    
    // if publishers enabled
    if (oNetyPublisherJoints.isConnected() &&     
        oNetyPublisherAxis.isConnected())
    {
        benabled = true;
        LOG4CXX_INFO(logger, modName + " initialized");                                
    }
    else
        LOG4CXX_ERROR(logger, modName + ": failed initialization, coms publishers not connected!");                        
}

void AmyBroadcaster::first()
{    
    log4cxx::NDC::push(modName);   	
}

void AmyBroadcaster::loop()
{      
    // get arm info in form of talky messages
    oComsOutArmSense.senseJoints(oNetyPublisherJoints);
    oComsOutArmSense.senseAxes(oNetyPublisherAxis);

    // publish joints category info
    oNetyPublisherJoints.process();
    oNetyPublisherJoints.flush();
    
    // publish axis category info
    oNetyPublisherAxis.process();
    oNetyPublisherAxis.flush();    
}

}