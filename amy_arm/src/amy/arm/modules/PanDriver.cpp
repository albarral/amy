/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/PanDriver.h"

using namespace log4cxx;

namespace amy
{
PanDriver::PanDriver()
{
    modName = "PanDriver";   
    pBusPan = 0;
}

//PanDriver::~PanDriver()
//{
//}

void PanDriver::createControllers(Arm& oArm)
{
    pJointControl = new JointControl();      // utility class to drive the HS
}

void PanDriver::setControlledJoint()
{
    pBusPan = &pArmBus->getPanBus();
    // controlled joint is HS
    pJointBus = &pArmBus->getBusHS();
}
       
void PanDriver::senseBus()
{
    // if pan requested, new move
    if (pBusPan->getCO_AXIS_POS().checkRequested())
    {
        targetAxis = pBusPan->getCO_AXIS_POS().getValue();  
        setState(eSTATE_NEWMOVE);   
    }

    // sense HS angle (soll value used here)
    istHS = pJointBus->getCO_JOINT_ANGLE().getValue();    
    // sense reached HS limits
    jointLimit = pJointBus->getSO_JOINT_LIMIT_REACHED().getValue();
}

float PanDriver::computeAxisPosition()
{
    return istHS;    // pan position = HS position
}
}