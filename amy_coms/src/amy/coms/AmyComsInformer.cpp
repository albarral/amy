/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/coms/AmyComsInformer.h"
#include "talky/Topics.h"
#include "talky/coms/MessageBlock.h"

namespace amy
{
log4cxx::LoggerPtr AmyComsInformer::logger(log4cxx::Logger::getLogger("amy.coms"));

AmyComsInformer::AmyComsInformer()
{    
    bconnected = false;
    pArmBus = 0;
    // prepare interpreter for arm topic communications
    oInterpreter.addLanguage(talky::Topics::eTOPIC_ARM);
}

void AmyComsInformer::connect2Arm(ArmBus& oArmBus)
{
    pArmBus = &oArmBus;
    if (pArmBus != 0)
        bconnected = true;
    else
        bconnected = false;
}
    
std::string AmyComsInformer::getArmInfo()
{  
    // return empty message if no interface connection    
    if (!bconnected)
    {
        LOG4CXX_ERROR(logger, "AmyComsInformer: can't fetch info, no arm interface connection");           
        return "";
    }
    
    // reset commands block
    oCommandBlock.reset();
    
    // fetch arm info into commands block
    oArmComsSensing.fetchArmInfo(pArmBus, oCommandBlock);  
        
    // transform commands block to message with the interpreter        
    talky::MessageBlock oMessageBlock;
    if (oInterpreter.buildMessageBlock(oCommandBlock, oMessageBlock))
    {
        //LOG4CXX_INFO(logger, "AmyComsInformer: message built - " + oMessageBlock.getRawText());      
        // if message built ok, return its raw text
        return oMessageBlock.getRawText();
    }
    else
    {
        // otherwise return empty message
        LOG4CXX_ERROR(logger, "AmyComsInformer: message could not be built!");    
        LOG4CXX_ERROR(logger, "AmyComsInformer: " + oCommandBlock.toString());    
        return "";
    }
}

}