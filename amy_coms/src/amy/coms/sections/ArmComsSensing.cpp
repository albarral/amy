/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/sections/ArmComsSensing.h"

namespace amy
{
log4cxx::LoggerPtr ArmComsSensing::logger(log4cxx::Logger::getLogger("amy.coms"));


bool ArmComsSensing::fetchArmInfo(iArmInterface* pArmInterface, talky::CommandBlock& oCommandBlock)
{
    bool bret = true;

    // skip if no interface connection
    if (pArmInterface == 0)
    {
        LOG4CXX_ERROR(logger, "ArmComsSensing: can't fetch info, no arm interface connection");           
        return false;
    }

    // fetch joints info
    bret = senseJointAngles(pArmInterface, oCommandBlock);
    talky::CommandBlock oCommandBlock2;     // TEMP to be given as parameter
    bret = senseJointStates(pArmInterface, oCommandBlock2);
    talky::CommandBlock oCommandBlock3;      // TEMP to be given as parameter
    bret = senseArmAxes(pArmInterface, oCommandBlock3);

    return bret;
}

bool ArmComsSensing::senseJointAngles(iArmInterface* pArmInterface, talky::CommandBlock& oCommandBlock)
{
    // skip if no interface connection
    if (pArmInterface == 0)
        return false;

    // read commanded control values of all joints ...
    oDataBlockJoints.setPosHS(pArmInterface->getHSControl());
    oDataBlockJoints.setPosVS(pArmInterface->getVSControl());
    oDataBlockJoints.setPosEL(pArmInterface->getELControl());
    oDataBlockJoints.setPosHW(pArmInterface->getHWControl());
    oDataBlockJoints.setPosVW(pArmInterface->getVWControl());

    // and convert them to a command block
    return oDataBlockJoints.writeBlock(oCommandBlock);
}

bool ArmComsSensing::senseJointStates(iArmInterface* pArmInterface, talky::CommandBlock& oCommandBlock)
{
    // skip if no interface connection
    if (pArmInterface == 0)
        return false;

    // read state of all joint drivers
//    oDataBlockJointDrivers.setStateHS(pArmInterface->getHSControl());
//    oDataBlockJointDrivers.setStateVS(pArmInterface->getVSControl());
//    oDataBlockJointDrivers.setStateEL(pArmInterface->getELControl());
//    oDataBlockJointDrivers.setStateHW(pArmInterface->getHWControl());
//    oDataBlockJointDrivers.setStateVW(pArmInterface->getVWControl());

    // and convert them to a command block
    return oDataBlockJointDrivers.writeBlock(oCommandBlock);
}

bool ArmComsSensing::senseArmAxes(iArmInterface* pArmInterface, talky::CommandBlock& oCommandBlock)
{
    // skip if no interface connection
    if (pArmInterface == 0)
        return false;

    // read commanded axes values and their sensed speeds
//    oDataBlockAxes.setPan(pArmInterface->getHSControl());
//    oDataBlockAxes.setTilt(pArmInterface->getVSControl());
//    oDataBlockAxes.setRadius(pArmInterface->getELControl());
//    oDataBlockAxes.setPanSpeed(pArmInterface->getHWControl());
//    oDataBlockAxes.setTiltSpeed(pArmInterface->getVWControl());

    // and convert them to a command block
    return oDataBlockAxes.writeBlock(oCommandBlock);
}

}