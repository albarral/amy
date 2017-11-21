/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/out/ArmComsSensing.h"
#include "talky/Topics.h"
#include "talky/coms/Command.h"
#include "talky/topics/ArmTopic.h"

namespace amy
{
log4cxx::LoggerPtr ArmComsSensing::logger(log4cxx::Logger::getLogger("amy.coms"));


ArmComsSensing::ArmComsSensing()
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

void ArmComsSensing::connect2Arm(ArmBus& oArmBus)
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

bool ArmComsSensing::senseJointAngles(talky::CommandBlock& oCommandBlock)
{
    // skip if no interface connection
    if (pBusHS == 0)
        return false;

    // read commanded control values of all joints ...
    oDataBlockJoints.setPosHS(pBusHS->getCO_JOINT_ANGLE().getValue());
    oDataBlockJoints.setPosVS(pBusVS->getCO_JOINT_ANGLE().getValue());
    oDataBlockJoints.setPosEL(pBusEL->getCO_JOINT_ANGLE().getValue());
    oDataBlockJoints.setPosHW(pBusHW->getCO_JOINT_ANGLE().getValue());
    oDataBlockJoints.setPosVW(pBusVW->getCO_JOINT_ANGLE().getValue());

    // and convert them to a command block
    return oDataBlockJoints.writeBlock(oCommandBlock);
}

bool ArmComsSensing::senseArmAxes(talky::CommandQueue& oCommandQueue)
{
    // skip if no interface connection
    if (pBusPan == 0)
        return false;
    
    // fill queue with commands of arm topic and axis category
    talky::Command oCommand;        
    oCommand.setTopic(talky::Topics::eTOPIC_ARM);
    oCommand.setCategory(talky::ArmTopic::eCAT_ARM_AXIS);
       
    // read commanded axes values and their sensed speeds
    // pan
    oCommand.setConcept(talky::ArmTopic::eAXIS_PAN_POS);
    oCommand.setQuantity(pBusPan->getCO_AXIS_POS().getValue());
    oCommandQueue.add(oCommand);
    // tilt
    oCommand.setConcept(talky::ArmTopic::eAXIS_TILT_POS);
    oCommand.setQuantity(pBusTilt->getCO_AXIS_POS().getValue());
    oCommandQueue.add(oCommand);
    // radius
    oCommand.setConcept(talky::ArmTopic::eAXIS_RAD_POS);
    oCommand.setQuantity(pBusRadial->getCO_AXIS_POS().getValue());
    oCommandQueue.add(oCommand);
    // pan speed
    oCommand.setConcept(talky::ArmTopic::eAXIS_PAN_SPEED);
    oCommand.setQuantity(pBusPan->getSO_AXIS_SPEED().getValue());
    oCommandQueue.add(oCommand);
    // tilt speed
    oCommand.setConcept(talky::ArmTopic::eAXIS_TILT_SPEED);
    oCommand.setQuantity(pBusTilt->getSO_AXIS_SPEED().getValue());
    oCommandQueue.add(oCommand);

    return true;
}

}