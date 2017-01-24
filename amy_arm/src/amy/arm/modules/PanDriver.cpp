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
}

//PanDriver::~PanDriver()
//{
//}


void PanDriver::connectOutput()
{
    // connect to HS joint (horizontal shoulder)
    pJointBus = &pArmBus->getBusHS();
}
       
void PanDriver::updateTarget()
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

    // record output for analysis
    //oRecord.reset();
    
    // show data
    LOG4CXX_INFO(logger, ">> new request");  
    LOG4CXX_INFO(logger, "target pan = " << targetValue);  
    LOG4CXX_INFO(logger, "ist HS = " << istJoint);
    LOG4CXX_INFO(logger, oJointControl.paramsToString());      
}

void PanDriver::senseBus()
{
    // get requested pan
    if (pArmBus->getCO_ARM_PAN().checkRequested())
    {
        targetValue = (int)pArmBus->getCO_ARM_PAN().getValue();    
        moveRequested();
    }

    // sense HS angle (soll value used here)
    istJoint = pJointBus->getCO_JOINT_ANGLE().getValue();
    
    // sense reached HS limits
    jointLimit = pJointBus->getSO_JCONTROL_LIMIT_REACHED().getValue();
}

}