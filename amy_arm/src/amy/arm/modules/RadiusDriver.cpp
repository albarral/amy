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
}

//RadiusDriver::~RadiusDriver()
//{
//}

void RadiusDriver::prepareDriver()
{
    // update movement params
    AxisDriver::prepareDriver();
    
    oRadialControl.setArmSize(pArm->getLenHumerus(), pArm->getLenRadius());
}

void RadiusDriver::connectOutput()
{
    // connect to ELB
    pJointBus = &pArmBus->getBusEL();
}
       
void RadiusDriver::updateTarget()
{
    // update movement params
    if (pJointControlConfig != 0)
    {
        oRadialControl.init(pJointControlConfig->getKaccelDriver(),
                               pJointControlConfig->getKspeedDriver(),
                               pJointControlConfig->getDriverTolerance(),
                               pJointControlConfig->getDriverSpeed());        
    }
        
    // set new target
    oRadialControl.setTargetRadius(targetValue);
    
    // show data
    LOG4CXX_INFO(logger, ">> new request");  
    LOG4CXX_INFO(logger, "target radius = " << targetValue);  
    LOG4CXX_INFO(logger, "ist ELB = " << istJoint);
    LOG4CXX_INFO(logger, oRadialControl.paramsToString());      
}

void RadiusDriver::senseBus()
{
    // get requested radius
    if (pArmBus->getCO_ARM_RADIUS().checkRequested())
    {
        targetValue = (int)pArmBus->getCO_ARM_RADIUS().getValue();    
        moveRequested();
    }

    // sense ELB angle (soll value used here)
    istJoint = pJointBus->getCO_JOINT_ANGLE().getValue();
    
    // sense reached ELB limits
    jointLimit = pJointBus->getSO_JCONTROL_LIMIT_REACHED().getValue();
}

}