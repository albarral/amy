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
    pBusFrontalCycler = 0;
    pBusPan = 0;
    pBusTilt = 0;
    pBusRadial = 0;
    pBusHS = 0;
    pBusVS = 0;
    pBusEL = 0;
    pBusHW = 0;
    pBusVW = 0;
}

void ArmInterface::connect(ArmBus& oArmBus)
{
    pArmBus = &oArmBus;
    pBusFrontalCycler = &oArmBus.getFrontalCyclerBus();
    pBusPan = &oArmBus.getPanBus();
    pBusTilt = &oArmBus.getTiltBus();
    pBusRadial = &oArmBus.getRadialBus();
    pBusHS = &oArmBus.getBusHS();
    pBusVS = &oArmBus.getBusVS();
    pBusEL = &oArmBus.getBusEL();
    pBusHW = &oArmBus.getBusHW();
    pBusVW = &oArmBus.getBusVW();
    benabled = true;
}


// ARM MOVER
void ArmInterface::launchMove(int value)
{
    if (benabled)
        pArmBus->getCO_MOVER_TYPE().request(value);                    
}
void ArmInterface::stopMove()
{
    if (benabled)
        pArmBus->getCO_MOVER_ACTION().request(false);                    
}
void ArmInterface::turnMove(int value)
{
    if (benabled)
        pArmBus->getCO_MOVER_TURN().request(value);                    
}
void ArmInterface::moveWider(bool value)
{
    if (benabled)
        pArmBus->getCO_MOVER_WIDER().request(value);                    
}
void ArmInterface::moveTaller(bool value)
{
    if (benabled)
        pArmBus->getCO_MOVER_TALLER().request(value);                    
}
void ArmInterface::moveFaster(bool value)
{
    if (benabled)
        pArmBus->getCO_MOVER_FASTER().request(value);                    
}

// CYCLERS
// set front cyclic frequency
void ArmInterface::frontFrequency(float value)
{
    if (benabled)
        pBusFrontalCycler->getCO_CYCLER_FREQ().request(value);                    
}
// set front amplitude (degrees)
void ArmInterface::frontAmplitude(float value)
{
    if (benabled)
        pBusFrontalCycler->getCO_CYCLER_AMPLITUDE().request(value);                    
}
// set front angle (degrees)
void ArmInterface::frontAngle(float value)
{
    if (benabled)
        pBusFrontalCycler->getCO_CYCLER_ANGLE().request(value);                    
}
// start/stop front cyclic movement
void ArmInterface::frontAction(bool bvalue)
{
    if (benabled)
        pBusFrontalCycler->getCO_CYCLER_ACTION().request(bvalue);                    
}

// AXIS SPEEDS
void ArmInterface::panSpeed(float value)
{    
    if (benabled)
        pBusPan->getCO_AXIS_SPEED().request(value);            
}
void ArmInterface::tiltSpeed(float value)
{    
    if (benabled)
        pBusTilt->getCO_AXIS_SPEED().request(value);            
}
void ArmInterface::radialSpeed(float value)
{    
    if (benabled)
        pBusRadial->getCO_AXIS_SPEED().request(value);            
}
void ArmInterface::keepTilt(int value)
{    
    if (benabled)
        pArmBus->getCO_KEEP_TILT().request(value);            
}
        
// AXIS POSITIONS
void ArmInterface::movePan(float angle)
{    
    int val = angle; // transform to int
    if (benabled)
        pBusPan->getCO_AXIS_POS().request(val);            
}
void ArmInterface::moveTilt(float angle)
{
    int val = angle; // transform to int
    if (benabled)
        pBusTilt->getCO_AXIS_POS().request(val);            
}
void ArmInterface::extend(float radius)
{
    int val = radius; // transform to int
    if (benabled)
        pBusRadial->getCO_AXIS_POS().request(val);            
}

// JOINT POSITIONS
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

// JOINT OUTPUTS    
float ArmInterface::getHSControl()
{
    if (benabled)
        return pBusHS->getCO_JOINT_ANGLE().getValue();    
    else
        return 0.0;
}
float ArmInterface::getVSControl()
{
    if (benabled)
        return pBusVS->getCO_JOINT_ANGLE().getValue();    
    else
        return 0.0;
}
float ArmInterface::getELControl()
{
    if (benabled)
        return pBusEL->getCO_JOINT_ANGLE().getValue();    
    else
        return 0.0;
}
float ArmInterface::getHWControl()
{
    if (benabled)
        return pBusHW->getCO_JOINT_ANGLE().getValue();    
    else
        return 0.0;
}
float ArmInterface::getVWControl()
{
    if (benabled)
        return pBusVW->getCO_JOINT_ANGLE().getValue();    
    else
        return 0.0;
}

}