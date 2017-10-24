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

    return bret;
}

bool ArmComsSensing::senseJointAngles(iArmInterface* pArmInterface, talky::CommandBlock& oCommandBlock)
{
    // skip if no interface connection
    if (pArmInterface == 0)
        return false;

    oArmJointAngles.reset();
    // read commanded control values of all joints ...
    oArmJointAngles.setPosHS(pArmInterface->getHSControl());
    oArmJointAngles.setPosVS(pArmInterface->getVSControl());
    oArmJointAngles.setPosEL(pArmInterface->getELControl());
    oArmJointAngles.setPosHW(pArmInterface->getHWControl());
    oArmJointAngles.setPosVW(pArmInterface->getVWControl());

    // and convert them to a command block
    return oArmJointAngles.writeJointPositions(oCommandBlock);
}

}