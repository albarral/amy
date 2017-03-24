/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/sections/CyclicServer.h"
#include "amy/coms/dictionary/CyclicCategory.h"

namespace amy
{
log4cxx::LoggerPtr CyclicServer::logger(log4cxx::Logger::getLogger("amy.server"));

CyclicServer::CyclicServer()
{    
    pArmInterface = 0;
}

void CyclicServer::connect2Arm(iArmInterface& oArmInterface)
{
    pArmInterface = &oArmInterface;
}

bool CyclicServer::processCommand(AmyCommand& oAmyCommand)
{
    bool bret = true;
    float value = oAmyCommand.getValue();

    switch (oAmyCommand.getAction())
    {
        case CyclicCategory::eCYCLIC_PAN_FREQ:
            LOG4CXX_INFO(logger, "> set pan freq " << value);                        
            panFrequency(value);
            break;
            
        case CyclicCategory::eCYCLIC_PAN_AMP:
            LOG4CXX_INFO(logger, "> set pan amplitude " << value);                        
            panAmplitude(value);
            break;

        case CyclicCategory::eCYCLIC_PAN_TRIGGER:
            LOG4CXX_INFO(logger, "> pan trigger ");                        
            panTrigger();
            break;

        case CyclicCategory::eCYCLIC_PAN_STOP:
            LOG4CXX_INFO(logger, "> pan stop ");                        
            panStop();
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "CyclicServer: untreated action " << oAmyCommand.getAction());           
    }    
    return bret;
}

// CYCLIC MOVEMENTS
void CyclicServer::panFrequency(float value)
{
    if (pArmInterface != 0)
        pArmInterface->panFrequency(value);
}
// set pan amplitude (degrees)
void CyclicServer::panAmplitude(float value)
{
    if (pArmInterface != 0)
        pArmInterface->panAmplitude(value);
}
// trigger pan cyclic movement
void CyclicServer::panTrigger()
{
    if (pArmInterface != 0)
        pArmInterface->panTrigger();
}
// stop pan cyclic movement
void CyclicServer::panStop()
{
    if (pArmInterface != 0)
        pArmInterface->panStop();
}
}