/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/coms/modules/ArmServer.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmServer::logger(Logger::getLogger("amy.coms"));

// Constructor 
ArmServer::ArmServer()
{    
    modName = "ArmServer";
    benabled = false;
 }

void ArmServer::init(ArmBus& oArmBus)
{
    // prepare communication servers
    oJointChannelServer.connect2Bus(oArmBus);    
    oAxisChannelServer.connect2Bus(oArmBus);    
    oCyclicChannelServer.connect2Bus(oArmBus);    
    oExtraChannelServer.connect2Bus(oArmBus);    
    
    // if servers enabled
    if (oJointChannelServer.isTuned() && 
        oAxisChannelServer.isTuned() && 
        oCyclicChannelServer.isTuned() && 
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
    // check cyclic channel
    checkChannelServer(oCyclicChannelServer);        
    // check extra channel
    checkChannelServer(oExtraChannelServer);        
}

bool ArmServer::checkChannelServer(tron::ChannelServer& oChannelServer)
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