/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/sections/ArmComsSensing.h"

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

bool ArmComsSensing::senseJointStates(talky::CommandBlock& oCommandBlock)
{
    // skip if no interface connection
    if (pBusHS == 0)
        return false;

    // read state of all joint drivers
    oDataBlockJointDrivers.setStateHS(pBusHS->getSO_DRIVER_STATE().getValue());
    oDataBlockJointDrivers.setStateVS(pBusVS->getSO_DRIVER_STATE().getValue());
    oDataBlockJointDrivers.setStateEL(pBusEL->getSO_DRIVER_STATE().getValue());
    oDataBlockJointDrivers.setStateHW(pBusHW->getSO_DRIVER_STATE().getValue());
    oDataBlockJointDrivers.setStateVW(pBusVW->getSO_DRIVER_STATE().getValue());

    // and convert them to a command block
    return oDataBlockJointDrivers.writeBlock(oCommandBlock);
}

bool ArmComsSensing::senseArmAxes(talky::CommandBlock& oCommandBlock)
{
    // skip if no interface connection
    if (pBusPan == 0)
        return false;

    // read commanded axes values and their sensed speeds
    oDataBlockAxes.setPan(pBusPan->getCO_AXIS_POS().getValue());
    oDataBlockAxes.setTilt(pBusTilt->getCO_AXIS_POS().getValue());
    oDataBlockAxes.setRadius(pBusRadial->getCO_AXIS_POS().getValue());
    oDataBlockAxes.setPanSpeed(pBusPan->getSO_AXIS_SPEED().getValue());
    oDataBlockAxes.setTiltSpeed(pBusTilt->getSO_AXIS_SPEED().getValue());

    // and convert them to a command block
    return oDataBlockAxes.writeBlock(oCommandBlock);
}

}