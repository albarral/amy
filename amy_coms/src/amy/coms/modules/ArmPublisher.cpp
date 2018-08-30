/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/coms/modules/ArmPublisher.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmPublisher::logger(Logger::getLogger("amy.coms"));

// Constructor 
ArmPublisher::ArmPublisher ()
{    
    modName = "ArmPublisher";
    benabled = false;
    // buses for joints
    pBusHS = 0;
    pBusVS = 0;
    pBusEL = 0;
    pBusHW = 0;
    pBusVW = 0;    
    // buses for axes
    pBusPan = 0;
    pBusTilt = 0;
    pBusRadial = 0;    
}

void ArmPublisher::init(ArmBus& oArmBus)
{
    // buses for joints
    pBusHS = &oArmBus.getBusHS();    
    pBusVS = &oArmBus.getBusVS();    
    pBusEL = &oArmBus.getBusEL();    
    pBusHW = &oArmBus.getBusHW();    
    pBusVW = &oArmBus.getBusVW();        
    // buses for axes
    pBusPan = &oArmBus.getPanBus();
    pBusTilt = &oArmBus.getTiltBus();
    pBusRadial = &oArmBus.getRadialBus();

    benabled = true;    
    LOG4CXX_INFO(logger, modName + " initialized");                                
}

void ArmPublisher::first()
{    
    log4cxx::NDC::push(modName);   	
}

void ArmPublisher::loop()
{      
    // publish channels data
    publishJointsSection();
    publishAxesSection();
}

void ArmPublisher::publishJointsSection()
{
    oJointsInformer.sendHS(pBusHS->getCO_JOINT_ANGLE().getValue());
    oJointsInformer.sendVS(pBusVS->getCO_JOINT_ANGLE().getValue());
    oJointsInformer.sendELB(pBusEL->getCO_JOINT_ANGLE().getValue());
    oJointsInformer.sendHWRI(pBusHW->getCO_JOINT_ANGLE().getValue());
    oJointsInformer.sendVWRI(pBusVW->getCO_JOINT_ANGLE().getValue());
}

void ArmPublisher::publishAxesSection()
{
    oAxesInformer.sendPan(pBusPan->getSO_AXIS_POS().getValue());
    oAxesInformer.sendTilt(pBusTilt->getSO_AXIS_POS().getValue());
    oAxesInformer.sendRadial(pBusRadial->getSO_AXIS_POS().getValue());
    oAxesInformer.sendPanSpeed(pBusPan->getSO_AXIS_SPEED().getValue());
    oAxesInformer.sendTiltSpeed(pBusTilt->getSO_AXIS_SPEED().getValue());
    oAxesInformer.sendRadialSpeed(pBusRadial->getSO_AXIS_SPEED().getValue());
}

}