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
    pArmBus = 0;
    // assign cycler servers
    oCycler1ChannelServer.setTargetCycler(AmyConfig::CYCLER1);
    oCycler2ChannelServer.setTargetCycler(AmyConfig::CYCLER2);
 }

void ArmServer::init(ArmBus& oArmBus)
{
    pArmBus = &oArmBus;
    
    // prepare communication servers
    oCycler1ChannelServer.connect2Bus(oArmBus);    
    oCycler2ChannelServer.connect2Bus(oArmBus);    
    oExtraChannelServer.connect2Bus(oArmBus);    
    
    // if servers enabled
    if (oCycler1ChannelServer.isTuned() && 
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
    // check joints section
    checkJointsSection();
    // check axes section
    checkAxesSection();

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

void ArmServer::checkJointsSection()
{
    float value;
    if (oJointsServer.getHS(value))
    {
        pArmBus->getBusHS().getCO_JOINT_ANGLE().request(value);
        LOG4CXX_INFO(logger, "> set HS " << value);                        
    }

    if (oJointsServer.getVS(value))
    {
        pArmBus->getBusVS().getCO_JOINT_ANGLE().request(value);
        LOG4CXX_INFO(logger, "> set VS " << value);                        
    }

    if (oJointsServer.getELB(value))
    {
        pArmBus->getBusEL().getCO_JOINT_ANGLE().request(value);
        LOG4CXX_INFO(logger, "> set ELB " << value);                        
    }

    if (oJointsServer.getHWRI(value))
    {
        pArmBus->getBusHW().getCO_JOINT_ANGLE().request(value);
        LOG4CXX_INFO(logger, "> set HW " << value);                        
    }

    if (oJointsServer.getVWRI(value))
    {
        pArmBus->getBusVW().getCO_JOINT_ANGLE().request(value);
        LOG4CXX_INFO(logger, "> set VW " << value);                        
    }

}

void ArmServer::checkAxesSection()
{
    float value;
    bool bvalue;
    if (oAxesServer.getPan(value))
    {
        pArmBus->getPanBus().getCO_AXIS_POS().request(value);
        LOG4CXX_INFO(logger, "> set pan " << value);                        
    }
    
    if (oAxesServer.getTilt(value))
    {
        pArmBus->getTiltBus().getCO_AXIS_POS().request(value);
        LOG4CXX_INFO(logger, "> set tilt " << value);                        
    }

    if (oAxesServer.getRadial(value))
    {
        pArmBus->getRadialBus().getCO_AXIS_POS().request(value);
        LOG4CXX_INFO(logger, "> set radius " << value);                        
    }

    if (oAxesServer.getPanSpeed(value))
    {
        pArmBus->getPanBus().getCO_AXIS_SPEED1().request(value);
        LOG4CXX_INFO(logger, "> pan speed " << value);                        
    }

    if (oAxesServer.getTiltSpeed(value))
    {
       pArmBus->getTiltBus().getCO_AXIS_SPEED1().request(value);
       LOG4CXX_INFO(logger, "> tilt speed " << value);                        
    }

    if (oAxesServer.getRadialSpeed(value))
    {
        pArmBus->getRadialBus().getCO_AXIS_SPEED1().request(value);
        LOG4CXX_INFO(logger, "> rad speed " << value);                                
    }

    if (oAxesServer.getKeepTilt(bvalue))
    {
        pArmBus->getCO_KEEP_TILT().request((int)bvalue);
        LOG4CXX_INFO(logger, "> keep tilt " << value);                        
    }    
}

}