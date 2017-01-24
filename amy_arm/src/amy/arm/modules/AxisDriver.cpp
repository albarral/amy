/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

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
    pJointBus = 0;        
    outAccel = 0;
}

//AxisDriver2::~AxisDriver2()
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
    connectOutput();
    if (pJointBus != 0)
    {
        bconnected = true;   
        LOG4CXX_DEBUG(logger, modName << " connected to bus");      
    }
    else        
        LOG4CXX_ERROR(logger, modName << " failed connection to out joint bus");              
}

void AxisDriver::prepareDriver()
{
    // update movement params
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
    // start at done
    bnewMove = false;    
    bmoveDone = true;
    bmoveBlocked = false;
    setState(eSTATE_DONE);
    
    log4cxx::NDC::push(modName);   	
}
                    
void AxisDriver::moveRequested()
{
    bnewMove = true;  
}

void AxisDriver::moveDone()
{
    bmoveDone = true;    
}

void AxisDriver::moveBlocked()
{
    bmoveBlocked = true;
}


// performs a cyclic wave movement of the elbow
void AxisDriver::loop()
{
    senseBus();
    
    // if new move requested -> go to DRIVE
    if (bnewMove)
    {
        bnewMove = false;    
        bmoveBlocked = false;
        bmoveDone = false;      
        // update movement's target (in derived class)
        updateTarget();        

        // record output for analysis
        // oRecord.reset();
        setState(eSTATE_DRIVE);
    }

    // skip if DONE  
    if (getState() == eSTATE_DONE)
        return;
        
    if (isStateChanged())
        showState();
      
    // otherwise,drive joint
    if (getState() == eSTATE_DRIVE)
    {
        // perform specific movement (in derived class)
        doMove();
        
        // if movement blocked or finished -> DONE
        if (bmoveBlocked || bmoveDone)
        {       
            setState(eSTATE_DONE);   
            showState();
        }
    }
                    
    // record output for analysis
    //oRecord.addElement(istSpeed, sollAccel);
    
    // send commands
    writeBus();        
}


void AxisDriver::doMove()
{
    // perform the control (compute the proper joint accel)
    JointControl& oJointControl = getController();        
    outAccel = oJointControl.drive(istJoint);
    
    LOG4CXX_INFO(logger, oJointControl.toString());
    
    // check if movement is blocked (pushing beyond the joint's limit)    
    if ((jointLimit > 0 && oJointControl.getMoveSign() > 0) || (jointLimit < 0 && oJointControl.getMoveSign() < 0))
        moveBlocked();
    
    // check if movement finished 
    if (oJointControl.isMovementDone())
        moveDone();  
}

void AxisDriver::writeBus()
{  
    // send command to joint (the computed acceleration)
    if (pJointBus != 0)
        pJointBus->getCO_JCONTROL_ACCEL().request(outAccel);
}

//void AxisDriver::done()
//{         
//    //Plot::plotRecord(oRecord, 60);
//}

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