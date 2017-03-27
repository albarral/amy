/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/RadiusDriver.h"

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

void RadiusDriver::prepareDriver()
{
    // set movement params
    AxisDriver::prepareDriver();
    
    oRadialPositioner.setArmSize(pArm->getLenHumerus(), pArm->getLenRadius());
}

void RadiusDriver::setControlledJoint()
{
    pBusRadial = &pArmBus->getRadialBus();
    // controlled joint is ELB
    pJointBus = &pArmBus->getBusEL();
}
       
void RadiusDriver::setNewTarget()
{
    // update movement params
    if (pArmConfig != 0)
    {
        oRadialPositioner.init(pArmConfig->getDriverKaccel(),
                               pArmConfig->getDriverKspeed(),
                               pArmConfig->getDriverTolerance(),
                               pArmConfig->getDriverSpeed());        
    }
        
    // prepare for new move
    oRadialPositioner.newRadialMove(targetAxis);
    
    // show data
    LOG4CXX_INFO(logger, ">> new request");  
    LOG4CXX_INFO(logger, "target radius = " << targetAxis);  
    LOG4CXX_INFO(logger, "ist ELB = " << istEL);
    LOG4CXX_INFO(logger, oRadialPositioner.paramsToString());      
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

void RadiusDriver::computeAxisPosition()
{
    // radial distance = function of EL position and arm lengths, BUT ...
    // only EL position used here -> as the RadialPositioner class internally computes the radial position itself
    istAxis = istEL;
}

}