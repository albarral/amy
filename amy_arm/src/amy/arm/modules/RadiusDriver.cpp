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
    pELBus = 0;    
}

//RadiusDriver::~RadiusDriver()
//{
//}

void RadiusDriver::prepareDriver()
{
    // set movement params
    AxisDriver::prepareDriver();
    
    oRadialControl.setArmSize(pArm->getLenHumerus(), pArm->getLenRadius());
}

void RadiusDriver::connectJoints()
{
    // connect output to EL joint
    pOutBus = &pArmBus->getBusEL();
    // connect input to EL joint 
    pELBus = &pArmBus->getBusEL();
}
       
void RadiusDriver::newMove()
{
    // update movement params
    if (pAmyArmConfig != 0)
    {
        oRadialControl.init(pAmyArmConfig->getDriverKaccel(),
                               pAmyArmConfig->getDriverKspeed(),
                               pAmyArmConfig->getDriverTolerance(),
                               pAmyArmConfig->getDriverSpeed());        
    }
        
    // prepare for new move
    oRadialControl.newRadialMove(targetAxis);
    
    // show data
    LOG4CXX_INFO(logger, ">> new request");  
    LOG4CXX_INFO(logger, "target radius = " << targetAxis);  
    LOG4CXX_INFO(logger, "ist ELB = " << istEL);
    LOG4CXX_INFO(logger, oRadialControl.paramsToString());      
}

void RadiusDriver::senseBus()
{
    // get requested radius
    if (pArmBus->getCO_ARM_RADIUS().checkRequested())
    {
        targetAxis = pArmBus->getCO_ARM_RADIUS().getValue();    
        setState(eSTATE_NEWMOVE);   
    }

    // sense EL angle (soll value used here)
    istEL = pELBus->getCO_JOINT_ANGLE().getValue();
    
    // sense reached EL limits
    jointLimit = pOutBus->getSO_JCONTROL_LIMIT_REACHED().getValue();
}

void RadiusDriver::computeAxisPosition()
{
    // used angle instead of axis (radial distance) needed for the RadialControl
    istAxis = istEL;
}

}