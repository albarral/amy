/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics  *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/AmyShow.h"
#include "talky/Topics.h"
#include "talky/coms/CommandBlock.h"

namespace amy
{
log4cxx::LoggerPtr AmyShow::logger(log4cxx::Logger::getLogger("amy.show"));

AmyShow::AmyShow() 
{
    // prepare interpreter for arm topic communications
    oInterpreter.addLanguage(talky::Topics::eTOPIC_ARM);    
    // prepare coms subscriber
    oComySubscriber.connect();    
}

AmyShow::~AmyShow()
{    
}
     
  void AmyShow::senseInfo()
{    
    // prepare coms subscriber
    if (!oComySubscriber.isConnected())
    {
        LOG4CXX_ERROR(logger, "AmyShow: failed connection of comy subscriber");
        return;
    }
    
    // read message and process it
    if (oComySubscriber.readMessage())
    {            
        processMessage(oComySubscriber.getRawMessage());            
    }            
  }

bool AmyShow::processMessage(std::string rawMessage)
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
            LOG4CXX_INFO(logger, "AmyShow: simple msg received, ignore");
        }            
    }
    else
    {
        LOG4CXX_ERROR(logger, "AmyShow: message processing failed!");            
    }

    return bret;    
}

}		
