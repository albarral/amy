/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/modules/ShowSenser.h"
#include "talky/Topics.h"
#include "talky/languages/ArmLanguage.h"

namespace amy
{
log4cxx::LoggerPtr ShowSenser::logger(log4cxx::Logger::getLogger("amy.show"));

// Constructor 
ShowSenser::ShowSenser()
{    
    modName = "ShowSenser";
    benabled = false;    
    pShowData = 0;
 }

ShowSenser::~ShowSenser()
{
}

void ShowSenser::init(ShowData& oShowData)
{
    pShowData = &oShowData;    
}

void ShowSenser::first()
{
    // prepare interpreter for arm topic communications
    oInterpreter.addLanguage(talky::Topics::eTOPIC_ARM);    
    
    talky::ArmLanguage oArmLanguage;    
    // prepare coms subscribers
    oComySubscriberJoints.connect(talky::Topics::ARM_TOPIC, oArmLanguage.CAT_ARM_JOINT);   
    oComySubscriberAxis.connect(talky::Topics::ARM_TOPIC, oArmLanguage.CAT_ARM_AXIS);    
    
    // if publishers enabled
    if (oComySubscriberJoints.isConnected() && 
            oComySubscriberAxis.isConnected() &&
            pShowData != 0)
    {
        benabled = true;
        LOG4CXX_INFO(logger, "ShowSenser initialized");                                
    }
    else
        LOG4CXX_ERROR(logger, "ShowSenser: failed initialization, coms subscribers not connected!");                            
}
                    
void ShowSenser::loop()
{
    // exit if not enabled
    if (!benabled)
    {
        LOG4CXX_ERROR(logger, "ShowSenser: not enabled, loop ignored");
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

bool ShowSenser::processMessage4Joints(std::string rawMessage)
{
    bool bret = false;

    // interpret received message
    if (oInterpreter.processMessage(rawMessage))
    {
        // if message block
        if (oInterpreter.isBlockProcessed())
        {
            // process interpreted command block
            bret = pShowData->getDataBlockJoints().readBlock(oInterpreter.getCommandBlock());
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

bool ShowSenser::processMessage4Axes(std::string rawMessage)
{
    bool bret = false;

    // interpret received message
    if (oInterpreter.processMessage(rawMessage))
    {
        // if message block
        if (oInterpreter.isBlockProcessed())
        {
            // process interpreted command block
            bret = pShowData->getDataBlockAxes().readBlock(oInterpreter.getCommandBlock());
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