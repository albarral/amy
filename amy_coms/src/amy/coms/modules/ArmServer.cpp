/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/coms/modules/ArmServer.h"
#include "amy/core/config/AmyConfig.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmServer::logger(Logger::getLogger("amy.coms"));

// Constructor 
ArmServer::ArmServer()
{    
    modName = "ArmServer";
    benabled = false;
    // assign cycler servers
    oCycler1ChannelServer.setTargetCycler(AmyConfig::CYCLER1);
    oCycler2ChannelServer.setTargetCycler(AmyConfig::CYCLER2);
 }

void ArmServer::init(ArmBus& oArmBus)
{
    // prepare communication servers
    oJointChannelServer.connect2Bus(oArmBus);    
    oAxisChannelServer.connect2Bus(oArmBus);    
    oCycler1ChannelServer.connect2Bus(oArmBus);    
    oCycler2ChannelServer.connect2Bus(oArmBus);    
    oExtraChannelServer.connect2Bus(oArmBus);    
    
    // if servers enabled
    if (oJointChannelServer.isTuned() && 
        oAxisChannelServer.isTuned() && 
        oCycler1ChannelServer.isTuned() && 
        oCycler2ChannelServer.isTuned() && 
        oExtraChannelServer.isTuned())
    {
        benabled = true;
        LOG4CXX_INFO(logger, modName + " initialized");                                
    }
    else
        LOG4CXX_ERROR(logger, modName + ": failed initialization, channel servers not tuned!");                        
}

void ArmServer::first()
{    
    log4cxx::NDC::push(modName);   	
}

void ArmServer::loop()
{
    // check joints channel
    checkChannelServer(oJointChannelServer);        
    // check axis channel
    checkChannelServer(oAxisChannelServer);        
    // check cycler1 channel
    checkChannelServer(oCycler1ChannelServer);        
    // check cycler2 channel
    checkChannelServer(oCycler2ChannelServer);        
    // check extra channel
    checkChannelServer(oExtraChannelServer);        
}

bool ArmServer::checkChannelServer(tron2::ChannelServer& oChannelServer)
{    
    // receive messages from the given channel
    if (oChannelServer.senseChannel())
    {
        // and process them
        oChannelServer.processCommands();
        return true;
    }
    // if no messages could be read
    else
        return false;
}

bool ArmServer::getAmyEndRequested()
{
    return oExtraChannelServer.getArmEndRequested();
}

}