/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/main/AmyListener.h"
#include "talky/Topics.h"
#include "talky/languages/ArmLanguage.h"

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

void AmyListener::init(ArmBus& oArmBus)
{
    talky::ArmLanguage oArmLanguage;
    // prepare communication servers
    oComyServerJoints.connect(talky::Topics::ARM_TOPIC, oArmLanguage.CAT_ARM_JOINT);
    oComyServerAxis.connect(talky::Topics::ARM_TOPIC, oArmLanguage.CAT_ARM_AXIS);
    oComyServerCyclic.connect(talky::Topics::ARM_TOPIC, oArmLanguage.CAT_ARM_CYCLIC);
    oComyServerExtra.connect(talky::Topics::ARM_TOPIC, oArmLanguage.CAT_ARM_EXTRA);    
    
    // prepare amy control server
    oAmyComsServer.connect2Arm(oArmBus);
    
    // if servers enabled
    if (oComyServerJoints.isConnected() && 
            oComyServerAxis.isConnected() &&
            oComyServerCyclic.isConnected() &&
            oComyServerExtra.isConnected() &&
            oAmyComsServer.isConnected())
    {
        benabled = true;
        LOG4CXX_INFO(logger, modName + " initialized");                                
    }
    else
        LOG4CXX_ERROR(logger, modName + ": failed initialization, coms servers not connected!");                        
}

void AmyListener::first()
{    
    log4cxx::NDC::push(modName);   	
}

void AmyListener::loop()
{
    // listen to joint messages
    if (oComyServerJoints.readMessage())
    {
        LOG4CXX_INFO(logger, modName + ": msg received - " + oComyServerJoints.getRawMessage());        
        // if something received process it
        oAmyComsServer.processMessage(oComyServerJoints.getRawMessage());
    }            

    // listen to axis messages
    if (oComyServerAxis.readMessage())
    {
        LOG4CXX_INFO(logger, modName + ": msg received - " + oComyServerAxis.getRawMessage());        
        // if something received process it
        oAmyComsServer.processMessage(oComyServerAxis.getRawMessage());
    }            

    // listen to cyclic messages
    if (oComyServerCyclic.readMessage())
    {
        LOG4CXX_INFO(logger, modName + ": msg received - " + oComyServerCyclic.getRawMessage());        
        // if something received process it
        oAmyComsServer.processMessage(oComyServerCyclic.getRawMessage());
    }            

    // listen to extra messages
    if (oComyServerExtra.readMessage())
    {
        LOG4CXX_INFO(logger, modName + ": msg received - " + oComyServerExtra.getRawMessage());        
        // if something received process it
        oAmyComsServer.processMessage(oComyServerExtra.getRawMessage());
    }            
}

bool AmyListener::checkAmyEndRequested()
{
    return oAmyComsServer.isAmyEndRequested();    
}
}