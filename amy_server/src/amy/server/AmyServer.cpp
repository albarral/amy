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
    pArmBus = 0;
    pBusHS = 0;
    pBusVS = 0;
    pBusEL = 0;
    pBusHW = 0;
    pBusVW = 0;
}

void AmyServer::connect(ArmBus* pArmBus)
{
    if (pArmBus != 0)
    {
        this->pArmBus = pArmBus;
        pBusHS = &pArmBus->getBusHS();
        pBusVS = &pArmBus->getBusVS();
        pBusEL = &pArmBus->getBusEL();
        pBusHW = &pArmBus->getBusHW();
        pBusVW = &pArmBus->getBusVW();
        bconnected = true;
    }
    
//    LOG4CXX_DEBUG(logger, "AmyServer connected to bus");      
}

void AmyServer::movePan(int value)
{    
    if (bconnected)
        pArmBus->getCO_ARM_PAN().request(value);            
}

void AmyServer::moveTilt(int value)
{
    if (bconnected)
        pArmBus->getCO_ARM_TILT().request(value);            
}

void AmyServer::moveRadius(int value)
{
    if (bconnected)
        pArmBus->getCO_ARM_RADIUS().request(value);            
}

void AmyServer::setPosHS(float value)
{
    if (bconnected)
         pBusHS->getCO_JOINT_ANGLE().request(value);    
}

void AmyServer::setPosVS(float value)
{
    if (bconnected)
         pBusVS->getCO_JOINT_ANGLE().request(value);        
}

void AmyServer::setPosELB(float value)
{
    if (bconnected)
         pBusEL->getCO_JOINT_ANGLE().request(value);        
}

void AmyServer::setPosHW(float value)
{
    if (bconnected)
         pBusHW->getCO_JOINT_ANGLE().request(value);            
}

void AmyServer::setPosVW(float value)
{
    if (bconnected)
         pBusVW->getCO_JOINT_ANGLE().request(value);            
}

void AmyServer::endAmy()
{
    if (bconnected)
        pArmBus->getCO_FINISH_MANAGER().request();            
}


}