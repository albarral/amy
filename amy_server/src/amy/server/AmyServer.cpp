/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/server/AmyServer.h"

namespace amy
{

AmyServer::AmyServer()
{    
    bconnected = false;
    pArmInterface = 0;
    bamyEndRequested = false;
}

void AmyServer::connect2Arm(iArmInterface& oArmInterface)
{
    pArmInterface = &oArmInterface;
    bconnected = true;
}

void AmyServer::movePan(float value)
{    
    if (bconnected)
        pArmInterface->movePan(value);
}

void AmyServer::moveTilt(float value)
{
    if (bconnected)
        pArmInterface->moveTilt(value);
}

void AmyServer::moveRadius(float value)
{
    if (bconnected)
        pArmInterface->extend(value);
}

void AmyServer::setPosHS(float value)
{
    if (bconnected)
        pArmInterface->moveHS(value);    
}

void AmyServer::setPosVS(float value)
{
    if (bconnected)
        pArmInterface->moveVS(value);    
}

void AmyServer::setPosELB(float value)
{
    if (bconnected)
        pArmInterface->moveEL(value);    
}

void AmyServer::setPosHW(float value)
{
    if (bconnected)
        pArmInterface->moveHW(value);    
}

void AmyServer::setPosVW(float value)
{
    if (bconnected)
        pArmInterface->moveVW(value);    
}

void AmyServer::endAmy()
{
    bamyEndRequested = true;    
}
}