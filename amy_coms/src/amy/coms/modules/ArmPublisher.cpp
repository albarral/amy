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
    pBusHS = 0;
    pBusVS = 0;
    pBusEL = 0;
    pBusHW = 0;
    pBusVW = 0;    
 }

void ArmPublisher::init(ArmBus& oArmBus)
{
    // buses for joints
    pBusHS = &oArmBus.getBusHS();    
    pBusVS = &oArmBus.getBusVS();    
    pBusEL = &oArmBus.getBusEL();    
    pBusHW = &oArmBus.getBusHW();    
    pBusVW = &oArmBus.getBusVW();        

    // prepare communication publishers
//    oAxisChannelPublisher.connect2Bus(oArmBus);
    
    // if publishers enabled
  //  if (oAxisChannelPublisher.isTuned())
    {
        benabled = true;
        LOG4CXX_INFO(logger, modName + " initialized");                                
    }
//    else
//        LOG4CXX_ERROR(logger, modName + ": failed initialization, channel publishers not tuned!");                        
}

void ArmPublisher::first()
{    
    log4cxx::NDC::push(modName);   	
}

void ArmPublisher::loop()
{      
    // sense channels data
//    oAxisChannelPublisher.senseData();
    
    // publish channels data
    publishJointsSection();
//    oAxisChannelPublisher.sendData();
}

void ArmPublisher::publishJointsSection()
{
    oJointsInformer.sendHS(pBusHS->getCO_JOINT_ANGLE().getValue());
    oJointsInformer.sendVS(pBusVS->getCO_JOINT_ANGLE().getValue());
    oJointsInformer.sendELB(pBusEL->getCO_JOINT_ANGLE().getValue());
    oJointsInformer.sendHWRI(pBusHW->getCO_JOINT_ANGLE().getValue());
    oJointsInformer.sendVWRI(pBusVW->getCO_JOINT_ANGLE().getValue());
}

}