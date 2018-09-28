/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/RadiusDriver.h"
#include "amy/arm/move/RadialControl.h"

using namespace log4cxx;

namespace amy
{
RadiusDriver::RadiusDriver()
{
    modName = "RadiusDriver";    
    pBusRadial = 0;
}

//RadiusDriver::~RadiusDriver()
//{
//}

void RadiusDriver::createControllers(Arm& oArm)
{
    pJointControl = new RadialControl(oArm.getLenHumerus(), oArm.getLenRadius());      // utility class to drive the ELB
}

void RadiusDriver::setControlledJoint()
{
    pBusRadial = &pArmBus->getRadialBus();
    // controlled joint is ELB
    pJointBus = &pArmBus->getBusEL();
}
       
void RadiusDriver::senseBus()
{
    // if radius requested, new move
    if (pBusRadial->getCO_AXIS_POS().checkRequested())
    {
        targetAxis = pBusRadial->getCO_AXIS_POS().getValue();    
        setState(eSTATE_NEWMOVE);   
    }

    // sense EL angle (soll value used here)
    istEL = pJointBus->getCO_JOINT_ANGLE().getValue();    
    // sense reached EL limits
    jointLimit = pJointBus->getSO_JOINT_LIMIT_REACHED().getValue();
}

float RadiusDriver::computeAxisPosition()
{
    // radial distance = function of EL position and arm lengths
    // but only EL position returned here as used RadialControl internally computes the radial position itself
    return istEL;
}

}