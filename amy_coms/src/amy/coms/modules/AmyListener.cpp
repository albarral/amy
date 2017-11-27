/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/coms/modules/AmyListener.h"
#include "talky/Topics.h"
#include "talky/topics/ArmTopic.h"
#include "tuly/utils/IntegerQueue.h"

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
    int topic = talky::Topics::eTOPIC_ARM;
    // prepare communication servers
    oNetyServerJoints.init(topic, talky::ArmTopic::eCAT_ARM_JOINT);
    oNetyServerAxis.init(topic, talky::ArmTopic::eCAT_ARM_AXIS);
    oNetyServerCyclic.init(topic, talky::ArmTopic::eCAT_ARM_CYCLIC);
    oNetyServerExtra.init(topic, talky::ArmTopic::eCAT_ARM_EXTRA);    
    
    oComsArmControl.connect2Arm(&oArmBus);
    
    // if servers enabled
    if (oNetyServerJoints.isConnected() && 
            oNetyServerAxis.isConnected() &&
            oNetyServerCyclic.isConnected() &&
            oNetyServerExtra.isConnected())
    {
        benabled = true;
        LOG4CXX_INFO(logger, modName + " initialized");                                
    }
    else
        LOG4CXX_ERROR(logger, modName + ": failed initialization, server nodes not connected!");                        
}

void AmyListener::first()
{    
    log4cxx::NDC::push(modName);   	
}

void AmyListener::loop()
{
    // listen to joint messages
    checkServer(oNetyServerJoints);
    // listen to axis messages
    checkServer(oNetyServerAxis);
    // listen to cyclic messages
    checkServer(oNetyServerCyclic);
    // listen to extra messages
    checkServer(oNetyServerExtra);
}

void AmyListener::checkServer(nety::NetNodeServer& oNetyServer)
{
    talky::Command oCommand;

    // get received messages
    oNetyServer.absorb();
    // process them to commands
    oNetyServer.process();
    // consume commands queue
    while (oNetyServer.hasCommands())
    {                    
        // process each command to a proper bus action
        if (oNetyServer.fetchCommand(oCommand))
        {
            LOG4CXX_INFO(logger, modName + ": cmd received - " + oCommand.toString());        
            oComsArmControl.processCommand(oCommand);
        }
    }                
}

bool AmyListener::checkSpecialActions()
{
    // clear all flags
    brequestedAmyEnd = false;
    brequestedGUIShow = false;
    brequestedGUIHide = false;

    tuly::IntegerQueue& oQueue = oComsArmControl.getQueueSpecialActions();
    int numActions = oQueue.getSize();
    int action; 
    // consume queue of special actions
    while (oQueue.isFilled())
    {
         oQueue.fetch(action);
         // set flags proper to requested actions    
         switch (action)
         {
             case ComsInArmControl::eACTION_AMY_END:
                 brequestedAmyEnd = true;
                 break;
             case ComsInArmControl::eACTION_SHOW_GUI:
                 brequestedGUIShow = true;
                 break;
             case ComsInArmControl::eACTION_HIDE_GUI:
                 brequestedGUIHide = true;
                 break;                 
         }
    }
        
    return (numActions > 0);    
}

}