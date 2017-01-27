/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/arm/modules/ArmExtender.h"

using namespace log4cxx;

namespace amy
{
ArmExtender::ArmExtender()
{
    modName = "ArmExtender";
    
    pBusVS = 0;
    pBusEL = 0;            
    vsAccel = 0;
    elbowAccel = 0;
}

//ArmExtender::~ArmExtender()
//{
//}

void ArmExtender::prepareDriver()
{
    // update movement params
    if (pJointControlConfig != 0)
    {
        oJointControl.init(pJointControlConfig->getKaccelDriver(),
                               pJointControlConfig->getKspeedDriver(),
                               pJointControlConfig->getDriverTolerance(),
                               pJointControlConfig->getDriverSpeed());   

        oRadialControl.init(pJointControlConfig->getKaccelDriver(),
                               pJointControlConfig->getKspeedDriver(),
                               pJointControlConfig->getDriverTolerance(),
                               pJointControlConfig->getDriverSpeed());                   
    }        
    
    oRadialControl.setArmSize(pArm->getLenHumerus(), pArm->getLenRadius());
    oArmMath.setLengths(pArm->getLenHumerus(), pArm->getLenRadius());    
}

void ArmExtender::connectDriver()
{
    // connect to vertical shoulder
    pBusVS = &pArmBus->getBusVS();
    // connect to elbow
    pBusEL = &pArmBus->getBusEL();
}


void ArmExtender::prepareMove()
{
    // update movement params
    if (pJointControlConfig != 0)
    {
        oJointControl.init(pJointControlConfig->getKaccelDriver(),
                       pJointControlConfig->getKspeedDriver(),
                       pJointControlConfig->getDriverTolerance(),
                       pJointControlConfig->getDriverSpeed());   

        oRadialControl.init(pJointControlConfig->getKaccelDriver(),
                               pJointControlConfig->getKspeedDriver(),
                               pJointControlConfig->getDriverTolerance(),
                               pJointControlConfig->getDriverSpeed());        
    }
        
    // set radius target
    oRadialControl.newRadialMove(targetRadius);
        
    // a temporal tilt position will be reached after the elbow movement (arm extension/retraction produces a tilt change)
    float finalEL = oRadialControl.getTargetAngle();           
    float finalTilt = oArmMath.computeTilt4JointAngles(istVS, finalEL);  
    
    // the right final tilt will then be reached after a VS corrective movement (with a VS displacement equal to the tilt deviation)
    float tiltDeviation = targetTilt - finalTilt;
    // set VS target
    oJointControl.newMove(istVS + tiltDeviation);
    
    // show data
    LOG4CXX_INFO(logger, ">> new request");  
    LOG4CXX_INFO(logger, "target tilt = " << targetTilt);  
    LOG4CXX_INFO(logger, "target radius = " << targetRadius);  
    LOG4CXX_INFO(logger, "ist VS = " << istVS);
    LOG4CXX_INFO(logger, "ist elbow = " << istElbow);
    LOG4CXX_INFO(logger, "finalEL = " << finalEL << "finalTilt = " << finalTilt << ", tilt deviation = " << tiltDeviation);
    LOG4CXX_INFO(logger, oJointControl.paramsToString());      
    LOG4CXX_INFO(logger, oRadialControl.paramsToString());      

}


void ArmExtender::doMove()
{
    // control the acceleration of both joints
    vsAccel = oJointControl.drive(istVS);
    elbowAccel = oRadialControl.drive(istElbow);
    LOG4CXX_INFO(logger, oJointControl.toString());
    LOG4CXX_INFO(logger, oRadialControl.toString());
    
    // check if any movement (VS or EL) is blocked (pushing beyond the joint's limit)    
    bool bmoveBlockedVS = ((vsLimitReached > 0 && oJointControl.getMoveSign() > 0) || (vsLimitReached < 0 && oJointControl.getMoveSign() < 0));
    bool bmoveBlockedEL = ((elbowLimitReached > 0 && oRadialControl.getMoveSign() > 0) || (elbowLimitReached < 0 && oRadialControl.getMoveSign() < 0));
    
    // movement is blocked when both joints are blocked
    if (bmoveBlockedVS && bmoveBlockedEL)
        moveBlocked();
    
    // movement is finished when both single movements are 
    if (oJointControl.isMovementDone() && oRadialControl.isMovementDone())
        moveDone();  
}

void ArmExtender::senseBus()
{
    bool btiltRequested = false;
    bool bradiusRequested = false;
    
    // get requested tilt
    if (pArmBus->getCO_ARM_TILT().checkRequested())
    {
        targetTilt = pArmBus->getCO_ARM_TILT().getValue();    
        btiltRequested = true;        
    }

    // get requested radius
    if (pArmBus->getCO_ARM_RADIUS().checkRequested())
    {
        targetRadius = pArmBus->getCO_ARM_RADIUS().getValue();    
        bradiusRequested = true;        
    }
        
    // sense VS and EL positions (soll values used)
    istVS = pBusVS->getCO_JOINT_ANGLE().getValue();  
    istElbow = pBusEL->getCO_JOINT_ANGLE().getValue();     
    
    // sense reached joint limits
    vsLimitReached = pBusVS->getSO_JCONTROL_LIMIT_REACHED().getValue();
    elbowLimitReached = pBusEL->getSO_JCONTROL_LIMIT_REACHED().getValue();

    // adapt to single requests (just radius or tilt)
    if (btiltRequested || bradiusRequested)
    {
        moveRequested();
        
        // if only radius requested, keep the present tilt 
        if (!btiltRequested)
            targetTilt = oArmMath.computeTilt4JointAngles(istVS, istElbow);  
        
        // if only tilt requested, keep the present radius
        if (!bradiusRequested)
            targetRadius = oArmMath.computeRadius4ElbowAngle(istElbow);            
    }
}

void ArmExtender::writeBus()
{  
    // control VS and EL joints
    pBusVS->getCO_JCONTROL_ACCEL().request(vsAccel);
    pBusEL->getCO_JCONTROL_ACCEL().request(elbowAccel);
}

}