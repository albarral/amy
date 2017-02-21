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
    
    pArmConfig = 0;
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

void AxisDriver::init(Arm& oArm, ArmConfig& oArmConfig)
{
    pArmConfig = &oArmConfig;      
    pArm = &oArm;
    // set specific preparation (in derived class)
    prepareDriver();
    benabled = true;

    LOG4CXX_INFO(logger, modName << " initialized");                  
    LOG4CXX_INFO(logger, oArmConfig.toString());      
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
    if (pArmConfig != 0)
    {
        // get used joint controller and initialize it
        JointPositioner& oJointControl = getController();        
        oJointControl.init(pArmConfig->getDriverKaccel(),
                               pArmConfig->getDriverKspeed(),
                               pArmConfig->getDriverTolerance(),
                               pArmConfig->getDriverSpeed());        
    }        
}

void AxisDriver::first()
{
    // start at done
    setState(eSTATE_DONE);
    log4cxx::NDC::push(modName);   	
}
                    

// drives the axis towards the target position
void AxisDriver::loop()
{
    senseBus();

    int state = getState();
    // skip if DONE or BLOCKED
    if (state == eSTATE_DONE ||state == eSTATE_BLOCKED)            
        return;
            
    switch (state)
    {
        case eSTATE_NEWMOVE:
            // new move requested -> update target & go to DRIVE
            newMove();        
            setState(eSTATE_DRIVE);
            break;

        case eSTATE_DRIVE:
            // drive joint
            // perform a move step
            if (doMove())
            {
                // if movement blocked -> BLOCKED
                if (checkBlocked())
                    setState(eSTATE_BLOCKED);   
            }
            // if movement finished -> DONE
            else 
                setState(eSTATE_DONE);   
            break;
    }   // end switch    

    if (isStateChanged())
        showState();

    writeBus();        
}


bool AxisDriver::doMove()
{
    computeAxisPosition();
    
    // perform the control (compute the proper joint accel)
    JointPositioner& oJointControl = getController();        
    outAccel = oJointControl.drive(istAxis);
    
    LOG4CXX_INFO(logger, oJointControl.toString());
    
    // check if movement finished 
    if (oJointControl.isMovementDone())
        return false;
    else
        return true;
}

bool AxisDriver::checkBlocked()
{
    int moveSign = getController().getMoveSign();

    // check if movement is blocked (pushing beyond the joint's limit)    
    return ((jointLimit > 0 && moveSign > 0) || (jointLimit < 0 && moveSign < 0));
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
                        
        case eSTATE_NEWMOVE:
            LOG4CXX_INFO(logger, ">> new move");
            break;

        case eSTATE_DRIVE:
            LOG4CXX_INFO(logger, ">> drive");
            break;

        case eSTATE_BLOCKED:
            LOG4CXX_INFO(logger, ">> blocked");
            break;
    }   // end switch    
}


}