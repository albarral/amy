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
    
    bconnected = false;
    pArmBus = 0;
    pJointBus = 0;    
    pJointControl = 0;
}

AxisDriver::~AxisDriver()
{
    if (pJointControl != 0)
        delete(pJointControl);
}

void AxisDriver::init(Arm& oArm, ArmConfig& oArmConfig)
{
    // control priority
    priority = oArmConfig.getPriority4AxisDrivers();
    // create proper joint controllers
    createControllers(oArm);
    // initialize joint controllers
    if (pJointControl != 0)
    {
        pJointControl->init(oArmConfig.getDriverKaccel(),
                               oArmConfig.getDriverKspeed(),
                               oArmConfig.getDriverTolerance(),
                               oArmConfig.getDriverSpeed());    

        LOG4CXX_INFO(logger, modName << pJointControl->paramsToString());              
        benabled = true;
        LOG4CXX_INFO(logger, modName << " initialized");                  
    }
    else
        LOG4CXX_WARN(logger, modName << " failed initialization!");                          
};

void AxisDriver::connect(ArmBus& oArmBus)
{
    pArmBus = &oArmBus;    
    // connect to controlled joint (defined in derived modules)
    setControlledJoint();    
    if (pJointBus != 0)
    {
        bconnected = true;   
        LOG4CXX_DEBUG(logger, modName << " connected to bus");      
    }
    else        
        LOG4CXX_ERROR(logger, modName << " failed connection to out joint bus");              
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

    if (getStable() == 0)
        showState();
    
    switch (state)
    {
        case eSTATE_NEWMOVE:
            // new move requested -> update target & go to DRIVE
            pJointControl->newMove(targetAxis);    
            outAccel = 0.0;
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

    writeBus();        
}


bool AxisDriver::doMove()
{
    istAxis = computeAxisPosition();
    
    // perform the control (compute the proper joint accel)
    outAccel = pJointControl->drive(istAxis);
    
    LOG4CXX_DEBUG(logger, pJointControl->toString());
    
    // check if movement finished 
    if (pJointControl->isMovementDone())
        return false;
    else
        return true;
}

bool AxisDriver::checkBlocked()
{
    // check if movement is blocked (pushing beyond the joint's limit)    
    if (jointLimit == 0)
        return false;
    // top limit and pushing up
    else if (jointLimit > 0)
        return (pJointControl->getMoveSign() > 0);
    // bottom limit and pushing down
    else 
        return (pJointControl->getMoveSign() < 0);
}

void AxisDriver::writeBus()
{  
    // send command to joint (the computed acceleration)
    pJointBus->getCO_JOINT_ACCEL().request(outAccel, priority);
}


void AxisDriver::showState()
{
    switch (getState())
    {
        case eSTATE_DONE:
            LOG4CXX_INFO(logger, ">> done");
            break;
                        
        case eSTATE_NEWMOVE:
            LOG4CXX_INFO(logger, ">> new move - target = " << targetAxis);
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