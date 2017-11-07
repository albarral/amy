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
    // prepare interpreter for arm topic communications
    oInterpreter.addLanguage(talky::Topics::eTOPIC_ARM);
}

void AmyComsInformer::connect2Arm(ArmBus& oArmBus)
{
    oArmComsSensing.connect2Arm(oArmBus);                   
    bconnected = true;
}
    
bool AmyComsInformer::getArmInfo()
{  
    // return empty message if no interface connection    
    if (!bconnected)
    {
        LOG4CXX_ERROR(logger, "AmyComsInformer: can't fetch info, no connection to arm bus");           
        return false;
    }
        
    // reset command blocks
    oCommandBlock1.reset();
    oCommandBlock2.reset();
    oCommandBlock3.reset();
    
    // fetch arm info into command blocks        
    bool bret1 = oArmComsSensing.senseJointAngles(oCommandBlock1);
    bool bret2 = oArmComsSensing.senseJointStates(oCommandBlock2);
    bool bret3 = oArmComsSensing.senseArmAxes(oCommandBlock3);
        
    if (!bret1 || !bret2 || !bret3)
    {
        LOG4CXX_ERROR(logger, "AmyComsInformer: error fetching arm info");           
        return false;        
    }
    
    // transform commands block to proper messages with the interpreter ...           
    talky::MessageBlock oMessageBlock;
    
    // message 1 (joint angles)
    if (oInterpreter.buildMessageBlock(oCommandBlock1, oMessageBlock))
    {
        // if message built ok, get its raw text
        messageJointAngles = oMessageBlock.getRawText();
    }
    else
    {
        // otherwise set empty message
        messageJointAngles = "";
        bret1 = false;
        LOG4CXX_ERROR(logger, "AmyComsInformer: message 1 could not be built!");    
        LOG4CXX_ERROR(logger, "AmyComsInformer: " + oCommandBlock1.toString());    
    }

    // message 2 (joint states)
    if (oInterpreter.buildMessageBlock(oCommandBlock2, oMessageBlock))
    {
        // if message built ok, get its raw text
        messageJointStates = oMessageBlock.getRawText();
    }
    else
    {
        // otherwise set empty message
        messageJointStates = "";
        bret2 = false;
        LOG4CXX_ERROR(logger, "AmyComsInformer: message 2 could not be built!");    
        LOG4CXX_ERROR(logger, "AmyComsInformer: " + oCommandBlock2.toString());    
    }
    
    // message 3 (axes)
    if (oInterpreter.buildMessageBlock(oCommandBlock3, oMessageBlock))
    {
        // if message built ok, get its raw text
        messageAxes = oMessageBlock.getRawText();
    }
    else
    {
        // otherwise set empty message
        messageAxes = "";
        bret3 = false;
        LOG4CXX_ERROR(logger, "AmyComsInformer: message 3 could not be built!");    
        LOG4CXX_ERROR(logger, "AmyComsInformer: " + oCommandBlock3.toString());    
    }
    
    return (bret1 && bret2 && bret3);
}

}