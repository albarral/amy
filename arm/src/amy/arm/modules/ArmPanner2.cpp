/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/ArmPanner2.h"


using namespace log4cxx;

namespace amy
{
ArmPanner2::ArmPanner2()
{
    modName = "ArmPanner2";
    
    pBusHS = 0;        
    panAccel = 0;
}

//ArmPanner2::~ArmPanner2()
//{
//}

void ArmPanner2::prepareDriver()
{
    // update movement params
    if (pMovementControl != 0)
    {
        oJointDriver.init(pMovementControl->getKaccelDriver(),
                               pMovementControl->getKspeedDriver(),
                               pMovementControl->getDriverTolerance(),
                               pMovementControl->getDriverSpeed());        
    }        
}

void ArmPanner2::connectDriver()
{
    // connect to HS joint (horizontal shoulder)
    pBusHS = &pBus->getBusHS();
}
       
void ArmPanner2::prepareMove()
{
    // update movement params
    if (pMovementControl != 0)
    {
        oJointDriver.init(pMovementControl->getKaccelDriver(),
                               pMovementControl->getKspeedDriver(),
                               pMovementControl->getDriverTolerance(),
                               pMovementControl->getDriverSpeed());        
    }
        
    // set new target
    oJointDriver.setTarget(targetPan);

    // record output for analysis
    //oRecord.reset();
    
    // show data
    showMovementData();                    
}

void ArmPanner2::doMove()
{
    panAccel = oJointDriver.drive(istPan);
    LOG4CXX_INFO(logger, oJointDriver.toString());
    
    // check if movement is blocked (pushing beyond the joint's limit)    
    if ((panLimitReached > 0 && oJointDriver.getMoveSign() > 0) || (panLimitReached < 0 && oJointDriver.getMoveSign() < 0))
        moveBlocked();
    
    // check if movement finished 
    if (oJointDriver.isMovementDone())
        moveDone();  
}

void ArmPanner2::senseBus()
{
    // get requested pan
    if (pBus->getCO_ARM_PAN().checkRequested())
    {
        targetPan = (int)pBus->getCO_ARM_PAN().getValue();    
        moveRequested();
    }

    // sense arm pan (soll value used here)
    istPan = pBusHS->getCO_JOINT_ANGLE().getValue();
    
    // sense joint speed (soll value used here)
    //istSpeed = pBusHS->getSO_JCONTROL_SPEED().getValue();

    // sense reached joint limits
    panLimitReached = pBusHS->getSO_JCONTROL_LIMIT_REACHED().getValue();
}


void ArmPanner2::writeBus()
{  
    // send HS acceleration
    pBusHS->getCO_JCONTROL_ACCEL().request(panAccel);
}


void ArmPanner2::showMovementData()
{
    LOG4CXX_INFO(logger, "target = " << targetPan);  
    LOG4CXX_INFO(logger, "ist = " << istPan);
    LOG4CXX_INFO(logger, oJointDriver.paramsToString());      
}

}