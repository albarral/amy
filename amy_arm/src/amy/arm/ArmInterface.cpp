/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/arm/ArmInterface.h"

namespace amy
{

ArmInterface::ArmInterface()
{    
    benabled = false;
    pArmBus = 0;
    pBusHS = 0;
    pBusVS = 0;
    pBusEL = 0;
    pBusHW = 0;
    pBusVW = 0;
}

void ArmInterface::connect(ArmBus& oArmBus)
{
    pArmBus = &oArmBus;
    pBusHS = &oArmBus.getBusHS();
    pBusVS = &oArmBus.getBusVS();
    pBusEL = &oArmBus.getBusEL();
    pBusHW = &oArmBus.getBusHW();
    pBusVW = &oArmBus.getBusVW();
    benabled = true;
}

// HIGH LEVEL CONTROL

void ArmInterface::movePan(float angle)
{    
    int val = angle; // transform to int
    if (benabled)
        pArmBus->getCO_ARM_PAN().request(val);            
}

void ArmInterface::moveTilt(float angle)
{
    int val = angle; // transform to int
    if (benabled)
        pArmBus->getCO_ARM_TILT().request(val);            
}

void ArmInterface::extend(float radius)
{
    int val = radius; // transform to int
    if (benabled)
        pArmBus->getCO_ARM_RADIUS().request(val);            
}

// LOW LEVEL CONTROL

void ArmInterface::moveHS(float angle)
{
    if (benabled)
         pBusHS->getCO_JOINT_ANGLE().request(angle);    
}

void ArmInterface::moveVS(float angle)
{
    if (benabled)
         pBusVS->getCO_JOINT_ANGLE().request(angle);        
}

void ArmInterface::moveEL(float angle)
{
    if (benabled)
         pBusEL->getCO_JOINT_ANGLE().request(angle);        
}

void ArmInterface::moveHW(float angle)
{
    if (benabled)
         pBusHW->getCO_JOINT_ANGLE().request(angle);            
}

void ArmInterface::moveVW(float angle)
{
    if (benabled)
         pBusVW->getCO_JOINT_ANGLE().request(angle);            
}

// LOW LEVEL OUTPUTS

// get HS control angle
float ArmInterface::getHSControl()
{
    if (benabled)
        return pBusHS->getCO_JOINT_ANGLE().getValue();    
    else
        return 0.0;
}

// get VS control angle
float ArmInterface::getVSControl()
{
    if (benabled)
        return pBusVS->getCO_JOINT_ANGLE().getValue();    
    else
        return 0.0;
}

// get EL control angle
float ArmInterface::getELControl()
{
    if (benabled)
        return pBusEL->getCO_JOINT_ANGLE().getValue();    
    else
        return 0.0;
}

// get HW control angle
float ArmInterface::getHWControl()
{
    if (benabled)
        return pBusHW->getCO_JOINT_ANGLE().getValue();    
    else
        return 0.0;
}

// get VW control angle
float ArmInterface::getVWControl()
{
    if (benabled)
        return pBusVW->getCO_JOINT_ANGLE().getValue();    
    else
        return 0.0;
}

}