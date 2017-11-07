/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics  *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/AmyShow.h"
#include "talky/Topics.h"
#include "talky/coms/CommandBlock.h"
#include "talky/languages/ArmLanguage.h"

namespace amy
{
log4cxx::LoggerPtr AmyShow::logger(log4cxx::Logger::getLogger("amy.show"));

AmyShow::AmyShow() 
{
    benabled = false;
    
    // prepare interpreter for arm topic communications
    oInterpreter.addLanguage(talky::Topics::eTOPIC_ARM);    
    
    talky::ArmLanguage oArmLanguage;    
    // prepare coms subscribers
    oComySubscriberJoints.connect(talky::Topics::ARM_TOPIC, oArmLanguage.CAT_ARM_JOINT);   
    oComySubscriberAxis.connect(talky::Topics::ARM_TOPIC, oArmLanguage.CAT_ARM_AXIS);    
    
    // if publishers enabled
    if (oComySubscriberJoints.isConnected() && 
            oComySubscriberAxis.isConnected())
    {
        benabled = true;
        LOG4CXX_INFO(logger, "AmyShow initialized");                                
    }
    else
        LOG4CXX_ERROR(logger, "AmyShow: failed initialization, coms subscribers not connected!");                            
}

AmyShow::~AmyShow()
{    
}
     
  void AmyShow::senseInfo()
{    
    // prepare coms subscriber
    if (!benabled)
    {
        LOG4CXX_ERROR(logger, "AmyShow: failed connection of comy subscriber");
        return;
    }
    
    // read joints message and process it
    if (oComySubscriberJoints.readMessage())
    {            
        processMessage4Joints(oComySubscriberJoints.getRawMessage());            
    }            

    // read axis message and process it
    if (oComySubscriberAxis.readMessage())
    {            
        processMessage4Axes(oComySubscriberAxis.getRawMessage());            
    }            
  }

bool AmyShow::processMessage4Joints(std::string rawMessage)
{
    bool bret = false;

    // interpret received message
    if (oInterpreter.processMessage(rawMessage))
    {
        // if message block
        if (oInterpreter.isBlockProcessed())
        {
            // process interpreted command block
            bret = oDataBlockJoints.readBlock(oInterpreter.getCommandBlock());
        }
        // if simple message
        else
        {
            LOG4CXX_WARN(logger, "AmyShow: simple msg received, ignore");
        }            
    }
    else
    {
        LOG4CXX_ERROR(logger, "AmyShow: joints message processing failed!");            
    }

    return bret;    
}

bool AmyShow::processMessage4Axes(std::string rawMessage)
{
    bool bret = false;

    // interpret received message
    if (oInterpreter.processMessage(rawMessage))
    {
        // if message block
        if (oInterpreter.isBlockProcessed())
        {
            // process interpreted command block
            bret = oDataBlockAxes.readBlock(oInterpreter.getCommandBlock());
        }
        // if simple message
        else
        {
            LOG4CXX_WARN(logger, "AmyShow: simple msg received, ignore");
        }            
    }
    else
    {
        LOG4CXX_ERROR(logger, "AmyShow: axes message processing failed!");            
    }

    return bret;    
}

}		
