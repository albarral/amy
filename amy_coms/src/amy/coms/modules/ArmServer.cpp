/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/coms/modules/ArmServer.h"
#include "amy/core/config/AmyConfig.h"
#include "amy/interface2/ArmNode.h"

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
    // buses for axes
    pBusPan = 0;
    pBusTilt = 0;
    pBusRadial = 0;    
    pCyclerBus1 = 0;
    pCyclerBus2 = 0;
    
    bEndRequested = false;
    // tune cycler servers
    oCyclerServer1.tune2Cycler(AmyConfig::CYCLER1);
    oCyclerServer2.tune2Cycler(AmyConfig::CYCLER2);
    // tune extra server
    ArmNode2 oArmNode;
    oExtraServer.init(oArmNode, ArmNode2::eSECTION_EXTRA);
 }

void ArmServer::init(ArmBus& oArmBus)
{
    pArmBus = &oArmBus;
    pBusPan = &(pArmBus->getPanBus());
    pBusTilt = &(pArmBus->getTiltBus());
    pBusRadial = &(pArmBus->getRadialBus());
    pCyclerBus1 = &(pArmBus->getCyclerBus1());
    pCyclerBus2 = &(pArmBus->getCyclerBus2());
    
    // prepare communication servers
    //oExtraChannelServer.connect2Bus(oArmBus);    
    
    // if servers enabled
    if (oCyclerServer1.isTuned() && oCyclerServer2.isTuned())
    {
        benabled = true;
        LOG4CXX_INFO(logger, modName + " initialized");                                
    }
    else
        LOG4CXX_ERROR(logger, modName + ": failed initialization, some servers not tuned!");                        
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
    // check cycler1 section
    checkCyclerSection(oCyclerServer1, pCyclerBus1, "cycler1");
    // check cycler2 section
    checkCyclerSection(oCyclerServer2, pCyclerBus2, "cycler2");
    // check extra section
    checkExtraSection();
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
        pBusPan->getCO_AXIS_POS().request(value);
        LOG4CXX_INFO(logger, "> set pan " << value);                        
    }
    
    if (oAxesServer.getTilt(value))
    {
        pBusTilt->getCO_AXIS_POS().request(value);
        LOG4CXX_INFO(logger, "> set tilt " << value);                        
    }

    if (oAxesServer.getRadial(value))
    {
        pBusRadial->getCO_AXIS_POS().request(value);
        LOG4CXX_INFO(logger, "> set radius " << value);                        
    }

    if (oAxesServer.getPanSpeed(value))
    {
        pBusPan->getCO_AXIS_SPEED1().request(value);
        LOG4CXX_INFO(logger, "> pan speed " << value);                        
    }

    if (oAxesServer.getTiltSpeed(value))
    {
       pBusTilt->getCO_AXIS_SPEED1().request(value);
       LOG4CXX_INFO(logger, "> tilt speed " << value);                        
    }

    if (oAxesServer.getRadialSpeed(value))
    {
        pBusRadial->getCO_AXIS_SPEED1().request(value);
        LOG4CXX_INFO(logger, "> rad speed " << value);                                
    }

    if (oAxesServer.getKeepTilt(bvalue))
    {
        pArmBus->getCO_KEEP_TILT().request((int)bvalue);
        LOG4CXX_INFO(logger, "> keep tilt " << value);                        
    }    
}

void ArmServer::checkCyclerSection(CyclerServer& oCyclerServer, CyclerBus* pCyclerBus, std::string identity)
{       
    float value;
    int ivalue;
    if (oCyclerServer.getMainFreq(value))
    {
        pCyclerBus->getCO_CYCLER_FREQ1().request(value);
        LOG4CXX_INFO(logger, identity << "main freq < " << value);                        
    }
    
    if (oCyclerServer.getMainAmplitude(value))
    {
        pCyclerBus->getCO_CYCLER_AMP1().request(value);
        LOG4CXX_INFO(logger, identity << "main amplitude < " << value);                        
    }

    if (oCyclerServer.getMainAngle(value))
    {
        pCyclerBus->getCO_CYCLER_ANGLE1().request(value);
        LOG4CXX_INFO(logger, identity << "main angle < " << value);                        
    }

    if (oCyclerServer.getMainPhase(value))
    {
        pCyclerBus->getCO_CYCLER_PHASE1().request((int)value);
        LOG4CXX_INFO(logger, identity << "main phase < " << value);                        
    }

    if (oCyclerServer.getSecondaryFreq(value))
    {
        pCyclerBus->getCO_CYCLER_FREQ2().request(value);
        LOG4CXX_INFO(logger, identity << "secondary freq < " << value);                        
    }
    
    if (oCyclerServer.getSecondaryAmplitude(value))
    {
        pCyclerBus->getCO_CYCLER_AMP2().request(value);
        LOG4CXX_INFO(logger, identity << "secondary amplitude < " << value);                        
    }

    if (oCyclerServer.getSecondaryAngle(value))
    {
        pCyclerBus->getCO_CYCLER_ANGLE2().request(value);
        LOG4CXX_INFO(logger, identity << "secondary angle < " << value);                        
    }

    if (oCyclerServer.getSecondaryPhase(value))
    {
        pCyclerBus->getCO_CYCLER_PHASE2().request((int)value);
        LOG4CXX_INFO(logger, identity << "secondary phase < " << value);                        
    }

    if (oCyclerServer.getAction(ivalue))
    {
        bool bgo = (ivalue != 0); 
        pCyclerBus->getCO_CYCLER_ACTION().request(bgo);
        LOG4CXX_INFO(logger, identity << " action < " << bgo);                        
    }
}

void ArmServer::checkExtraSection()
{
    if (oExtraServer.getStop())
    {
        pArmBus->getCO_ARM_STOP().request(true);
        LOG4CXX_INFO(logger, "> stop");                        
    }

    if (oExtraServer.getEnd())
    {
        bEndRequested = true;
        LOG4CXX_INFO(logger, "> end arm");  
    }
}

}