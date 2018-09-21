/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/coms/modules/ArmServer.h"
#include "amy/core/config/AmyConfig.h"
#include "amy/core/bus/CyclerBus.h"
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
    // check cycler1 channel
    checkCyclerSection(1);
    // check cycler2 channel
    checkCyclerSection(2);
    // check extra channel
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

void ArmServer::checkCyclerSection(int i)
{
    // security check
    if (i<1 && i>2) 
        return; 
        
    // select cycler server to use
    CyclerServer& oCyclerServer = (i==1) ? oCyclerServer1 : oCyclerServer2;        
    CyclerBus& oCyclerBus = (i==1) ? pArmBus->getCyclerBus1() : pArmBus->getCyclerBus2(); 
    std::string identity = (i==1) ? "> cycler1 " : "> cycler2 ";
       
    float value;
    int ivalue;
    if (oCyclerServer.getMainFreq(value))
    {
        oCyclerBus.getCO_CYCLER_FREQ1().request(value);
        LOG4CXX_INFO(logger, identity << "main freq " << value);                        
    }
    
    if (oCyclerServer.getMainAmplitude(value))
    {
        oCyclerBus.getCO_CYCLER_AMP1().request(value);
        LOG4CXX_INFO(logger, identity << "main amplitude " << value);                        
    }

    if (oCyclerServer.getMainAngle(value))
    {
        oCyclerBus.getCO_CYCLER_ANGLE1().request(value);
        LOG4CXX_INFO(logger, identity << "main angle " << value);                        
    }

    if (oCyclerServer.getMainPhase(value))
    {
        oCyclerBus.getCO_CYCLER_PHASE1().request((int)value);
        LOG4CXX_INFO(logger, identity << "main phase " << value);                        
    }

    if (oCyclerServer.getSecondaryFreq(value))
    {
        oCyclerBus.getCO_CYCLER_FREQ2().request(value);
        LOG4CXX_INFO(logger, identity << "secondary freq " << value);                        
    }
    
    if (oCyclerServer.getSecondaryAmplitude(value))
    {
        oCyclerBus.getCO_CYCLER_AMP2().request(value);
        LOG4CXX_INFO(logger, identity << "secondary amplitude " << value);                        
    }

    if (oCyclerServer.getSecondaryAngle(value))
    {
        oCyclerBus.getCO_CYCLER_ANGLE2().request(value);
        LOG4CXX_INFO(logger, identity << "secondary angle " << value);                        
    }

    if (oCyclerServer.getSecondaryPhase(value))
    {
        oCyclerBus.getCO_CYCLER_PHASE2().request((int)value);
        LOG4CXX_INFO(logger, identity << "secondary phase " << value);                        
    }

    if (oCyclerServer.getAction(ivalue))
    {
        bool bgo = (ivalue != 0); 
        oCyclerBus.getCO_CYCLER_ACTION().request(bgo);
        LOG4CXX_INFO(logger, identity << " action " << bgo);                        
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