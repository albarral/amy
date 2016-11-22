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
    if (pMovementControl != 0)
    {
        oJointDriver.init(pMovementControl->getKaccelDriver(),
                               pMovementControl->getKspeedDriver(),
                               pMovementControl->getDriverTolerance(),
                               pMovementControl->getDriverSpeed());   

        oRadialDriver.init(pMovementControl->getKaccelDriver(),
                               pMovementControl->getKspeedDriver(),
                               pMovementControl->getDriverTolerance(),
                               pMovementControl->getDriverSpeed());                   
    }        
    
    oRadialDriver.setArmSize(pArm->getLenHumerus(), pArm->getLenRadius());
    oArmMath.setLengths(pArm->getLenHumerus(), pArm->getLenRadius());    
}

void ArmExtender::connectDriver()
{
    // connect to vertical shoulder
    pBusVS = &pBus->getBusVS();
    // connect to elbow
    pBusEL = &pBus->getBusEL();
}


void ArmExtender::prepareMove()
{
    // update movement params
    if (pMovementControl != 0)
    {
        oJointDriver.init(pMovementControl->getKaccelDriver(),
                       pMovementControl->getKspeedDriver(),
                       pMovementControl->getDriverTolerance(),
                       pMovementControl->getDriverSpeed());   

        oRadialDriver.init(pMovementControl->getKaccelDriver(),
                               pMovementControl->getKspeedDriver(),
                               pMovementControl->getDriverTolerance(),
                               pMovementControl->getDriverSpeed());        
    }
        
    // set radius target
    oRadialDriver.setTargetRadius(targetRadius);
        
    // a temporal tilt position will be reached after the elbow movement (arm extension/retraction produces a tilt change)
    float finalEL = oRadialDriver.getTargetAngle();           
    float finalTilt = oArmMath.convJoints2ArmTilt(istVS, finalEL);  
    
    // the right final tilt will then be reached after a VS corrective movement (with a VS displacement equal to the tilt deviation)
    float tiltDeviation = targetTilt - finalTilt;
    // set VS target
    oJointDriver.setTarget(istVS + tiltDeviation);
    
    // show data
    LOG4CXX_INFO(logger, ">> new request");  
    LOG4CXX_INFO(logger, "target tilt = " << targetTilt);  
    LOG4CXX_INFO(logger, "target radius = " << targetRadius);  
    LOG4CXX_INFO(logger, "ist VS = " << istVS);
    LOG4CXX_INFO(logger, "ist elbow = " << istElbow);
    LOG4CXX_INFO(logger, "finalEL = " << finalEL << "finalTilt = " << finalTilt << ", tilt deviation = " << tiltDeviation);
    LOG4CXX_INFO(logger, oJointDriver.paramsToString());      
    LOG4CXX_INFO(logger, oRadialDriver.paramsToString());      

}


void ArmExtender::doMove()
{
    // control the acceleration of both joints
    vsAccel = oJointDriver.drive(istVS);
    elbowAccel = oRadialDriver.drive(istElbow);
    LOG4CXX_INFO(logger, oJointDriver.toString());
    LOG4CXX_INFO(logger, oRadialDriver.toString());
    
    // check if any movement (VS or EL) is blocked (pushing beyond the joint's limit)    
    bool bmoveBlockedVS = ((vsLimitReached > 0 && oJointDriver.getMoveSign() > 0) || (vsLimitReached < 0 && oJointDriver.getMoveSign() < 0));
    bool bmoveBlockedEL = ((elbowLimitReached > 0 && oRadialDriver.getMoveSign() > 0) || (elbowLimitReached < 0 && oRadialDriver.getMoveSign() < 0));
    
    // movement is blocked when both joints are blocked
    if (bmoveBlockedVS && bmoveBlockedEL)
        moveBlocked();
    
    // movement is finished when both single movements are 
    if (oJointDriver.isMovementDone() && oRadialDriver.isMovementDone())
        moveDone();  
}

void ArmExtender::senseBus()
{
    bool btiltRequested = false;
    bool bradiusRequested = false;
    
    // get requested tilt
    if (pBus->getCO_ARM_TILT().checkRequested())
    {
        targetTilt = pBus->getCO_ARM_TILT().getValue();    
        btiltRequested = true;        
    }

    // get requested radius
    if (pBus->getCO_ARM_RADIUS().checkRequested())
    {
        targetRadius = pBus->getCO_ARM_RADIUS().getValue();    
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
            targetTilt = oArmMath.convJoints2ArmTilt(istVS, istElbow);  
        
        // if only tilt requested, keep the present radius
        if (!bradiusRequested)
            targetRadius = oArmMath.convJoints2ArmRadius(istElbow);            
    }
}

void ArmExtender::writeBus()
{  
    // control VS and EL joints
    pBusVS->getCO_JCONTROL_ACCEL().request(vsAccel);
    pBusEL->getCO_JCONTROL_ACCEL().request(elbowAccel);
}

}