/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/ArmElbow.h"


using namespace log4cxx;

namespace amy
{
ArmElbow::ArmElbow()
{
    modName = "ArmElbow";
    
    pBusElbow = 0;        
    elbowAccel = 0;
}

//ArmElbow::~ArmElbow()
//{
//}

void ArmElbow::prepareDriver()
{
    // update movement params
    if (pJointControlConfig != 0)
    {
        oRadialDriver.init(pJointControlConfig->getKaccelDriver(),
                               pJointControlConfig->getKspeedDriver(),
                               pJointControlConfig->getDriverTolerance(),
                               pJointControlConfig->getDriverSpeed());        
    }        
    
    oRadialDriver.setArmSize(pArm->getLenHumerus(), pArm->getLenRadius());
}

void ArmElbow::connectDriver()
{
    // connect to ELBOW joint 
    pBusElbow = &pArmBus->getBusEL();
}
       
void ArmElbow::prepareMove()
{
    // update movement params
    if (pJointControlConfig != 0)
    {
        oRadialDriver.init(pJointControlConfig->getKaccelDriver(),
                               pJointControlConfig->getKspeedDriver(),
                               pJointControlConfig->getDriverTolerance(),
                               pJointControlConfig->getDriverSpeed());        
    }
        
    // set new target
    oRadialDriver.setTargetRadius(targetRadius);

    // record output for analysis
    //oRecord.reset();
    
    // show data
    LOG4CXX_INFO(logger, ">> new request");  
    LOG4CXX_INFO(logger, "target radius = " << targetRadius);  
    LOG4CXX_INFO(logger, "ist elbow = " << istElbow);
    LOG4CXX_INFO(logger, oRadialDriver.paramsToString());      
}

void ArmElbow::doMove()
{
    elbowAccel = oRadialDriver.drive(istElbow);
    LOG4CXX_INFO(logger, oRadialDriver.toString());
    
    // check if movement is blocked (pushing beyond the joint's limit)    
    if ((elbowLimitReached > 0 && oRadialDriver.getMoveSign() > 0) || (elbowLimitReached < 0 && oRadialDriver.getMoveSign() < 0))
        moveBlocked();
    
    // check if movement finished 
    if (oRadialDriver.isMovementDone())
        moveDone();  
}

void ArmElbow::senseBus()
{
    // get requested radius
    if (pArmBus->getCO_ARM_RADIUS().checkRequested())
    {
        targetRadius = pArmBus->getCO_ARM_RADIUS().getValue();    
        moveRequested();
    }

    // sense arm pan (soll value used here)
    istElbow = pBusElbow->getCO_JOINT_ANGLE().getValue();
    
    // sense reached elbow limits
    elbowLimitReached = pBusElbow->getSO_JCONTROL_LIMIT_REACHED().getValue();
}


void ArmElbow::writeBus()
{  
    // send HS acceleration
    pBusElbow->getCO_JCONTROL_ACCEL().request(elbowAccel);
}

}