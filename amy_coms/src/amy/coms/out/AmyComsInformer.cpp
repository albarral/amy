/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/coms/out/AmyComsInformer.h"
#include "talky/Topics.h"
#include "talky/coms/Message.h"
#include "talky/coms/MessageBlock.h"
#include "talky/coms/Command.h"

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
    oAxesCommandQueue.clean();
    
    // fetch arm info into command blocks        
    bool bret1 = oArmComsSensing.senseJointAngles(oCommandBlock1);
    bool bret2 = oArmComsSensing.senseArmAxes(oAxesCommandQueue);
        
    if (!bret1 || !bret2)
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
    
    // update messages queue for axis cat
    oAxesMessageQueue.clean();
    if (oAxesCommandQueue.isFilled())
        convertCommands2Messages(oAxesCommandQueue, oAxesMessageQueue);

    return (bret1 && bret2);
}

void AmyComsInformer::convertCommands2Messages(talky::CommandQueue& oCommandQueue, tuly::MessageQueue& oMessageQueue)
{
    talky::Command oCommand;        
    talky::Message oMessage;
    
    while (oCommandQueue.isFilled())
    {
        if (oCommandQueue.fetch(oCommand))
        {
            // build message from command
            if (oInterpreter.buildSimpleMessage(oCommand, oMessage))
            {
                oMessageQueue.add(oMessage.getRawText());                
            }
        }            
    }
}

}