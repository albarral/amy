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


void PanDriver::setControlledJoint()
{
    pBusPan = &pArmBus->getPanBus();
    // controlled joint is HS
    pJointBus = &pArmBus->getBusHS();
}
       
void PanDriver::setNewTarget()
{
    // update movement params
    if (pArmConfig != 0)
    {
        oJointPositioner.init(pArmConfig->getDriverKaccel(),
                               pArmConfig->getDriverKspeed(),
                               pArmConfig->getDriverTolerance(),
                               pArmConfig->getDriverSpeed());        
    }
        
    // prepare for new move
    oJointPositioner.setNewMove(targetAxis);
    
    // show data
    LOG4CXX_INFO(logger, ">> new request");  
    LOG4CXX_INFO(logger, "target pan = " << targetAxis);  
    LOG4CXX_INFO(logger, "ist HS = " << istHS);
    LOG4CXX_INFO(logger, oJointPositioner.paramsToString());      
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

void PanDriver::computeAxisPosition()
{
    istAxis = istHS;    // pan position = HS position
}
}