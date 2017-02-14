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
    pHSBus = 0;
}

//PanDriver::~PanDriver()
//{
//}


void PanDriver::connectJoints()
{
    // connect output to HS joint 
    pOutBus = &pArmBus->getBusHS();
    // connect input to HS joint 
    pHSBus = &pArmBus->getBusHS();
}
       
void PanDriver::newMove()
{
    // update movement params
    if (pArmConfig != 0)
    {
        oJointControl.init(pArmConfig->getDriverKaccel(),
                               pArmConfig->getDriverKspeed(),
                               pArmConfig->getDriverTolerance(),
                               pArmConfig->getDriverSpeed());        
    }
        
    // prepare for new move
    oJointControl.newMove(targetAxis);
    
    // show data
    LOG4CXX_INFO(logger, ">> new request");  
    LOG4CXX_INFO(logger, "target pan = " << targetAxis);  
    LOG4CXX_INFO(logger, "ist HS = " << istHS);
    LOG4CXX_INFO(logger, oJointControl.paramsToString());      
}

void PanDriver::senseBus()
{
    // get requested pan
    if (pArmBus->getCO_ARM_PAN().checkRequested())
    {
        targetAxis = pArmBus->getCO_ARM_PAN().getValue();  
        setState(eSTATE_NEWMOVE);   
    }

    // sense HS angle (soll value used here)
    istHS = pHSBus->getCO_JOINT_ANGLE().getValue();
    
    // sense reached HS limits
    jointLimit = pOutBus->getSO_JCONTROL_LIMIT_REACHED().getValue();
}

void PanDriver::computeAxisPosition()
{
    istAxis = istHS;    // the axis is directly the joint
}
}