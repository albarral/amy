/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/coms/modules/AmyListener.h"
#include "talky/Topics.h"
#include "talky/languages/ArmLanguage.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AmyListener::logger(Logger::getLogger("amy.coms"));

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
    std::string message;
    // listen to joint messages
    oComyServerJoints.readMessages();
    while (oComyServerJoints.hasMessages())
    {
        message = oComyServerJoints.getMessage();
        if (!message.empty())
        {
            LOG4CXX_INFO(logger, modName + ": msg received - " + message);        
            // if something received process it
            oAmyComsServer.processMessage(message, oComsData);
        }
    }            

    // listen to axis messages
    oComyServerAxis.readMessages();
    while (oComyServerAxis.hasMessages())
    {
        message = oComyServerAxis.getMessage();
        if (!message.empty())
        {
            LOG4CXX_INFO(logger, modName + ": msg received - " + message);        
            // if something received process it
            oAmyComsServer.processMessage(message, oComsData);
        }
    }            

    // listen to cyclic messages
    oComyServerCyclic.readMessages();
    while (oComyServerCyclic.hasMessages())
    {
        message = oComyServerCyclic.getMessage();
        if (!message.empty())
        {
            LOG4CXX_INFO(logger, modName + ": msg received - " + message);        
            // if something received process it
            oAmyComsServer.processMessage(message, oComsData);
        }
    }            

    // listen to extra messages
    oComyServerExtra.readMessages();
    while (oComyServerExtra.hasMessages())
    {
        message = oComyServerExtra.getMessage();
        if (!message.empty())
        {
            LOG4CXX_INFO(logger, modName + ": msg received - " + message);        
            // if something received process it
            oAmyComsServer.processMessage(message, oComsData);
        }
    }            
}

bool AmyListener::checkSpecialActions()
{
    return oComsData.hasPendingActions();
}

void AmyListener::clearSpecialActions()
{
    oComsData.reset();    
}
}