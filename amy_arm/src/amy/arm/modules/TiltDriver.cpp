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
    pVSBus = 0;
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

void TiltDriver::connectJoints()
{
    // connect output to VS joint 
    pOutBus = &pArmBus->getBusVS();
    // connect input 1 to VS joint 
    pVSBus = &pArmBus->getBusVS();
    // connect input 2 to EL joint 
    pELBus = &pArmBus->getBusEL();
}
       
void TiltDriver::newMove()
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
    oJointPositioner.newMove(targetAxis);
    
    // show data
    LOG4CXX_INFO(logger, ">> new request");  
    LOG4CXX_INFO(logger, "target tilt = " << targetAxis);  
    LOG4CXX_INFO(logger, "ist VS = " << istVS);
    LOG4CXX_INFO(logger, "ist EL = " << istEL);
    LOG4CXX_INFO(logger, oJointPositioner.paramsToString());      
}

void TiltDriver::senseBus()
{
    // get requested tilt
    if (pArmBus->getCO_ARM_TILT().checkRequested())
    {
        targetAxis = pArmBus->getCO_ARM_TILT().getValue();    
        setState(eSTATE_NEWMOVE);    
    }

    // sense VS and EL angles (soll value used here)
    istVS = pVSBus->getCO_JOINT_ANGLE().getValue();
    istEL = pELBus->getCO_JOINT_ANGLE().getValue();

    // sense reached VS limits
    jointLimit = pOutBus->getSO_JCONTROL_LIMIT_REACHED().getValue();
}

void TiltDriver::computeAxisPosition()
{
    // compute present tilt axis angle
    istAxis = oArmMath.computeTilt4JointAngles(istVS, istEL);
}

}