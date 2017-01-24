/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/TiltDriver.h"

using namespace log4cxx;

namespace amy
{
TiltDriver::TiltDriver()
{
    modName = "TiltDriver";    
}

//TiltDriver::~TiltDriver()
//{
//}

void TiltDriver::connectOutput()
{
    // connect to VS joint 
    pJointBus = &pArmBus->getBusVS();
}
       
void TiltDriver::updateTarget()
{
    // update movement params
    if (pJointControlConfig != 0)
    {
        oJointControl.init(pJointControlConfig->getKaccelDriver(),
                               pJointControlConfig->getKspeedDriver(),
                               pJointControlConfig->getDriverTolerance(),
                               pJointControlConfig->getDriverSpeed());        
    }
        
    // set new target
    oJointControl.setTarget(targetValue);
    
    // show data
    LOG4CXX_INFO(logger, ">> new request");  
    LOG4CXX_INFO(logger, "target tilt = " << targetValue);  
    LOG4CXX_INFO(logger, "ist VS = " << istJoint);
    LOG4CXX_INFO(logger, oJointControl.paramsToString());      
}

void TiltDriver::senseBus()
{
    // get requested tilt
    if (pArmBus->getCO_ARM_TILT().checkRequested())
    {
        targetValue = (int)pArmBus->getCO_ARM_TILT().getValue();    
        moveRequested();
    }

    // sense VS angle (soll value used here)
    istJoint = pJointBus->getCO_JOINT_ANGLE().getValue();
    
    // sense reached VS limits
    jointLimit = pJointBus->getSO_JCONTROL_LIMIT_REACHED().getValue();
}

}