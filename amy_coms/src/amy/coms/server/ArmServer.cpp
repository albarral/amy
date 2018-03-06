/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "ArmServer.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmServer::logger(Logger::getLogger("tron_test"));

ArmServer::ArmServer()
{        
}

//ArmServer::~ArmServer()
//{    
//}

void ArmServer::connect2Bus(ArmBus& oArmBus)
{
    oJointChannelServer.connect2Bus(oArmBus);    
}

bool ArmServer::checkChannels()
{
    // check joints channel
    checkChannelServer(oJointChannelServer);        
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

}