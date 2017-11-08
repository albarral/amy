/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/coms/modules/AmyBroadcaster.h"
#include "talky/Topics.h"
#include "talky/languages/ArmLanguage.h"

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
    talky::ArmLanguage oArmLanguage;    
    // prepare communication publishers
    oComyPublisherJoints.connect(talky::Topics::ARM_TOPIC, oArmLanguage.CAT_ARM_JOINT);
    //oComyPublisherAxis.connect(talky::Topics::ARM_TOPIC, oArmLanguage.CAT_ARM_AXIS);
    // prepare amy sensor informer
    oAmyComsInformer.connect2Arm(oArmBus);
    
    // if publishers enabled
    if (oComyPublisherJoints.isConnected() &&             
            oAmyComsInformer.isConnected())
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
    // if info obtained, broadcast them
    if (oAmyComsInformer.getArmInfo())
    {
        oComyPublisherJoints.publishMessage(oAmyComsInformer.getMessage4JointAngles());
        //oComyPublisherAxis.publishMessage(oAmyComsInformer.getMessage4Axes());
    }
}

}