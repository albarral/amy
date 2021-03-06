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

void TiltDriver::createControllers(Arm& oArm)
{
    pJointControl = new JointControl();      // utility class to drive the VS
    // tune arm math
    oArmMath.setLengths(oArm.getLenHumerus(), oArm.getLenRadius());
}

void TiltDriver::setControlledJoint()
{
    pBusTilt = &pArmBus->getTiltBus();
     // controlled joint is VS
    pJointBus = &pArmBus->getBusVS();
    // use EL joint for axis position computation
    pELBus = &pArmBus->getBusEL();
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
    jointLimit = pJointBus->getSO_JOINT_LIMIT_REACHED().getValue();
    // sense EL angle for axis pos computation (soll value used here)
    istEL = pELBus->getCO_JOINT_ANGLE().getValue();
}

float TiltDriver::computeAxisPosition()
{
    // tilt position = function of VS and EL positions
    return oArmMath.computeTilt4JointAngles(istVS, istEL);
}

}