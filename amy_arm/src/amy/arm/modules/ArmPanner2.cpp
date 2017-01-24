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
    if (pJointControlConfig != 0)
    {
        oJointControl.init(pJointControlConfig->getKaccelDriver(),
                               pJointControlConfig->getKspeedDriver(),
                               pJointControlConfig->getDriverTolerance(),
                               pJointControlConfig->getDriverSpeed());        
    }        
}

void ArmPanner2::connectDriver()
{
    // connect to HS joint (horizontal shoulder)
    pBusHS = &pArmBus->getBusHS();
}
       
void ArmPanner2::prepareMove()
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
    oJointControl.setTarget(targetPan);

    // record output for analysis
    //oRecord.reset();
    
    // show data
    LOG4CXX_INFO(logger, ">> new request");  
    LOG4CXX_INFO(logger, "target pan = " << targetPan);  
    LOG4CXX_INFO(logger, "ist HS = " << istPan);
    LOG4CXX_INFO(logger, oJointControl.paramsToString());      
}

void ArmPanner2::doMove()
{
    panAccel = oJointControl.drive(istPan);
    LOG4CXX_INFO(logger, oJointControl.toString());
    
    // check if movement is blocked (pushing beyond the joint's limit)    
    if ((panLimitReached > 0 && oJointControl.getMoveSign() > 0) || (panLimitReached < 0 && oJointControl.getMoveSign() < 0))
        moveBlocked();
    
    // check if movement finished 
    if (oJointControl.isMovementDone())
        moveDone();  
}

void ArmPanner2::senseBus()
{
    // get requested pan
    if (pArmBus->getCO_ARM_PAN().checkRequested())
    {
        targetPan = (int)pArmBus->getCO_ARM_PAN().getValue();    
        moveRequested();
    }

    // sense arm pan (soll value used here)
    istPan = pBusHS->getCO_JOINT_ANGLE().getValue();
    
    // sense reached HS limits
    panLimitReached = pBusHS->getSO_JCONTROL_LIMIT_REACHED().getValue();
}


void ArmPanner2::writeBus()
{  
    // send HS acceleration
    pBusHS->getCO_JCONTROL_ACCEL().request(panAccel);
}

}