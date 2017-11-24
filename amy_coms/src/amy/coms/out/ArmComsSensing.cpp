/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/out/ArmComsSensing.h"
#include "talky/Topics.h"
#include "talky/topics/ArmTopic.h"

namespace amy
{
log4cxx::LoggerPtr ComsArmSensing::logger(log4cxx::Logger::getLogger("amy.coms"));


ComsArmSensing::ComsArmSensing()
{
    pBusHS = 0;
    pBusVS = 0;
    pBusEL = 0;
    pBusHW = 0;
    pBusVW = 0;
    pBusPan = 0;
    pBusTilt = 0;
    pBusRadial = 0;    
}

void ComsArmSensing::connect2Arm(ArmBus& oArmBus)
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
}

bool ComsArmSensing::senseJoints(nety::NetNodePublisher& oNetyPublisher)
{
    // skip if no interface connection
    if (pBusHS == 0)
        return false;

    // read commanded control values of all joints ...
    oNetyPublisher.addCommand(talky::ArmTopic::eJOINT_HS_POS, pBusHS->getCO_JOINT_ANGLE().getValue());
    oNetyPublisher.addCommand(talky::ArmTopic::eJOINT_VS_POS, pBusVS->getCO_JOINT_ANGLE().getValue());
    oNetyPublisher.addCommand(talky::ArmTopic::eJOINT_ELB_POS, pBusEL->getCO_JOINT_ANGLE().getValue());
    oNetyPublisher.addCommand(talky::ArmTopic::eJOINT_HWRI_POS, pBusHW->getCO_JOINT_ANGLE().getValue());
    oNetyPublisher.addCommand(talky::ArmTopic::eJOINT_VWRI_POS, pBusVW->getCO_JOINT_ANGLE().getValue());

    return (oNetyPublisher.getSizeCommandsQueue() > 0);
}

bool ComsArmSensing::senseAxes(nety::NetNodePublisher& oNetyPublisher)
{
    // skip if no interface connection
    if (pBusPan == 0)
        return false;
           
    // read commanded axes values and their sensed speeds
    // pan    
    oNetyPublisher.addCommand(talky::ArmTopic::eAXIS_PAN_POS, pBusPan->getCO_AXIS_POS().getValue());
    // tilt
    oNetyPublisher.addCommand(talky::ArmTopic::eAXIS_TILT_POS, pBusTilt->getCO_AXIS_POS().getValue());
    // radius
    oNetyPublisher.addCommand(talky::ArmTopic::eAXIS_RAD_POS, pBusRadial->getCO_AXIS_POS().getValue());
    // pan speed
    oNetyPublisher.addCommand(talky::ArmTopic::eAXIS_PAN_SPEED, pBusPan->getSO_AXIS_SPEED().getValue());
    // tilt speed
    oNetyPublisher.addCommand(talky::ArmTopic::eAXIS_TILT_SPEED, pBusTilt->getSO_AXIS_SPEED().getValue());

    return (oNetyPublisher.getSizeCommandsQueue() > 0);
}

}