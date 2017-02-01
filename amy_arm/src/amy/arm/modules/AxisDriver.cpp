/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include "log4cxx/ndc.h"

#include "amy/arm/modules/AxisDriver.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AxisDriver::logger(Logger::getLogger("amy.arm"));

AxisDriver::AxisDriver()
{
    benabled = false;
    modName = "AxisDriver";
    
    pJointControlConfig = 0;
    pArm = 0;        
        
    bconnected = false;
    pArmBus = 0;
    pOutBus = 0;        
    priority = 2;
    outAccel = 0;
}

//AxisDriver::~AxisDriver()
//{
//}

void AxisDriver::init(Arm& oArm, JointControlConfig& oJointControlConfig)
{
    pJointControlConfig = &oJointControlConfig;      
    pArm = &oArm;
    // set specific preparation (in derived class)
    prepareDriver();
    benabled = true;

    LOG4CXX_INFO(logger, modName << " initialized");                  
    LOG4CXX_INFO(logger, oJointControlConfig.toString());      
};

void AxisDriver::connect(ArmBus& oArmBus)
{
    pArmBus = &oArmBus;
    // set output connection (in derived class)
    connectJoints();
    if (pOutBus != 0)
    {
        bconnected = true;   
        LOG4CXX_DEBUG(logger, modName << " connected to bus");      
    }
    else        
        LOG4CXX_ERROR(logger, modName << " failed connection to out joint bus");              
}

void AxisDriver::prepareDriver()
{
    // set movement params
    if (pJointControlConfig != 0)
    {
        // get used joint controller and initialize it
        JointControl& oJointControl = getController();        
        oJointControl.init(pJointControlConfig->getKaccelDriver(),
                               pJointControlConfig->getKspeedDriver(),
                               pJointControlConfig->getDriverTolerance(),
                               pJointControlConfig->getDriverSpeed());        
    }        
}

void AxisDriver::first()
{
    setState(eSTATE_DONE);
    // start at done
    oMoveState.moveDone();
    
    log4cxx::NDC::push(modName);   	
}
                    

// drives the axis towards the target position
void AxisDriver::loop()
{
    senseBus();
    
    // if new move requested -> go to DRIVE
    if (oMoveState.isRequested())
    {
        // update movement's target (in derived class)
        newMove();        
        oMoveState.moveGoing();
        setState(eSTATE_DRIVE);
    }

    // skip if DONE  
    if (getState() == eSTATE_DONE)
        return;
        
    if (isStateChanged())
        showState();
      
    // drive joint
    if (getState() == eSTATE_DRIVE)
    {
        // perform a move step
        doMove();        
        writeBus();        
        // if movement blocked or finished -> DONE
        if (oMoveState.isBlocked() || oMoveState.isDone())            
        {
            setState(eSTATE_DONE);   
            showState();
        }
    }
}


void AxisDriver::doMove()
{
    computeAxisPosition();
    
    // perform the control (compute the proper joint accel)
    JointControl& oJointControl = getController();        
    outAccel = oJointControl.drive(istAxis);
    
    LOG4CXX_INFO(logger, oJointControl.toString());
    
    // check if movement is blocked (pushing beyond the joint's limit)    
    if ((jointLimit > 0 && oJointControl.getMoveSign() > 0) || (jointLimit < 0 && oJointControl.getMoveSign() < 0))
        oMoveState.moveBlocked();
    
    // check if movement finished 
    if (oJointControl.isMovementDone())
        oMoveState.moveDone();  
}


void AxisDriver::writeBus()
{  
    // send command to joint (the computed acceleration)
    if (pOutBus != 0)
        pOutBus->getCO_JCONTROL_ACCEL().request(outAccel, priority);
}


void AxisDriver::showState()
{
    switch (getState())
    {
        case eSTATE_DONE:
            LOG4CXX_INFO(logger, ">> done");
            break;
                        
        case eSTATE_DRIVE:
            LOG4CXX_INFO(logger, ">> drive");
            break;
    }   // end switch    
}


}