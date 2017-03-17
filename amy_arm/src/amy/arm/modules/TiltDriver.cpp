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
    pBusTilt = 0;
    pELBus = 0;
}

//TiltDriver::~TiltDriver()
//{
//}

void TiltDriver::prepareDriver()
{
    // set movement params
    AxisDriver::prepareDriver();
    // tune arm math
    oArmMath.setLengths(pArm->getLenHumerus(), pArm->getLenRadius());
}

void TiltDriver::setControlledJoint()
{
    pBusTilt = &pArmBus->getTiltBus();
     // controlled joint is VS
    pJointBus = &pArmBus->getBusVS();
    // use EL joint for axis position computation
    pELBus = &pArmBus->getBusEL();
}
       
void TiltDriver::setNewTarget()
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
    LOG4CXX_INFO(logger, "target tilt = " << targetAxis);  
    LOG4CXX_INFO(logger, "ist VS = " << istVS);
    LOG4CXX_INFO(logger, "ist EL = " << istEL);
    LOG4CXX_INFO(logger, oJointPositioner.paramsToString());      
}

void TiltDriver::senseBus()
{
    // if tilt requested, new move
    if (pBusTilt->getCO_AXIS_POS().checkRequested())
    {
        targetAxis = pBusTilt->getCO_AXIS_POS().getValue();    
        setState(eSTATE_NEWMOVE);    
    }

    // sense VS angle (soll value used here)
    istVS = pJointBus->getCO_JOINT_ANGLE().getValue();
    // sense reached VS limits
    jointLimit = pJointBus->getSO_JCONTROL_LIMIT_REACHED().getValue();
    // sense EL angle for axis pos computation (soll value used here)
    istEL = pELBus->getCO_JOINT_ANGLE().getValue();
}

void TiltDriver::computeAxisPosition()
{
    // tilt position = function of VS and EL positions
    istAxis = oArmMath.computeTilt4JointAngles(istVS, istEL);
}

}