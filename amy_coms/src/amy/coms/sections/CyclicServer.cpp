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
        // FRONTAL CYCLER
        case CyclicCategory::eCYCLIC_FRONT_FREQ:
            LOG4CXX_INFO(logger, "> set front freq " << value);                        
            frontFrequency(value);
            break;
            
        case CyclicCategory::eCYCLIC_FRONT_AMP:
            LOG4CXX_INFO(logger, "> set front amplitude " << value);                        
            frontAmplitude(value);
            break;

        case CyclicCategory::eCYCLIC_FRONT_ANGLE:
            LOG4CXX_INFO(logger, "> set front angle ");                        
            frontAngle(value);
            break;

        case CyclicCategory::eCYCLIC_FRONT_START:
            LOG4CXX_INFO(logger, "> front start ");                        
            frontStart();
            break;

        case CyclicCategory::eCYCLIC_FRONT_STOP:
            LOG4CXX_INFO(logger, "> front stop ");                        
            frontStop();
            break;

       // ARM MOVER            
        case CyclicCategory::eCYCLIC_MOVER_LAUNCH:
            LOG4CXX_INFO(logger, "> set tilt freq " << value);                        
            tiltFrequency(value);
            break;
            
        case CyclicCategory::eCYCLIC_MOVER_STOP:
            LOG4CXX_INFO(logger, "> set tilt amplitude " << value);                        
            tiltAmplitude(value);
            break;

        case CyclicCategory::eCYCLIC_MOVER_TURN:
            LOG4CXX_INFO(logger, "> tilt trigger ");                        
            tiltTrigger();
            break;

        case CyclicCategory::eCYCLIC_MOVER_WIDER:
            LOG4CXX_INFO(logger, "> tilt stop ");                        
            tiltStop();
            break;

        case CyclicCategory::eCYCLIC_MOVER_TALLER:
            LOG4CXX_INFO(logger, "> tilt stop ");                        
            tiltStop();
            break;

        case CyclicCategory::eCYCLIC_MOVER_FASTER:
            LOG4CXX_INFO(logger, "> tilt stop ");                        
            tiltStop();
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "CyclicServer: untreated action " << oAmyCommand.getAction());           
    }    
    return bret;
}


// FRONTAL CYCLER
// set front cyclic frequency
void CyclicServer::frontFrequency(float value)
{
    if (pArmInterface != 0)
        pArmInterface->frontFrequency(value);
}
// set front amplitude (degrees)
void CyclicServer::frontAmplitude(float value)
{
    if (pArmInterface != 0)
        pArmInterface->frontAmplitude(value);
}
// set front cyclic angle
void CyclicServer::frontAngle(float value)
{
    if (pArmInterface != 0)
        pArmInterface->frontAngle(value);
}
// start front cyclic movement
void CyclicServer::frontStart()
{
    if (pArmInterface != 0)
        pArmInterface->frontAction(true);
}
// stop front cyclic movement
void CyclicServer::frontStop()
{
    if (pArmInterface != 0)
        pArmInterface->frontAction(false);
}


// ARM MOVER            
void CyclicServer::launchMove(int value)
{
    if (pArmInterface != 0)
        pArmInterface->launchMove(value);
}
void CyclicServer::stopMove()
{
    if (pArmInterface != 0)
        pArmInterface->stopMove();
}
void CyclicServer::turnMove(int value)
{
    if (pArmInterface != 0)
        pArmInterface->turnMove(value);
}
void CyclicServer::moveWider(bool value)
{
    if (pArmInterface != 0)
        pArmInterface->moveWider(value);
}
void CyclicServer::moveTaller(bool value)
{
    if (pArmInterface != 0)
        pArmInterface->moveTaller(value);
}
void CyclicServer::moveFaster(bool value)
{
    if (pArmInterface != 0)
        pArmInterface->moveFaster(value);
}
}