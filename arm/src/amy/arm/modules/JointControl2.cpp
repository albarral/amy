/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/JointControl2.h"
#include "amy/arm/config/ArmConfig.h"
#include "amy/robot/Joint.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr JointControl2::logger(Logger::getLogger("amy.arm"));

JointControl2::JointControl2()
{
    modName = "jcontrol2";
}

//JointControl2::~JointControl2()
//{
//}

void JointControl2::init(Arm& oArm)
{
    Joint* pJoint = oArm.getJointByName(jointName);
    oJointMover.init(pJoint->getLowerLimit(), pJoint->getUpperLimit());
    benabled = true;

    LOG4CXX_INFO(logger, modName << " initialized");      
    LOG4CXX_DEBUG(logger, "joint range= " << pJoint->getLowerLimit() << ", " << pJoint->getUpperLimit());
};


void JointControl2::first()
{
    setState(JointControl2::eSTATE_FREE);
    setNextState(JointControl2::eSTATE_FREE);
        
    log4cxx::NDC::push(modName);   	
}
                    
void JointControl2::loop()
{    
    senseBus();

    if (updateState())   
        showState();
         
    // update elapsed times
    oJointMover.click();
    oJointBrake.click();
     
    switch (getState())
    {
        case eSTATE_FREE:            

            // auto brake
            if (istSpeed != 0.0)
            {
                oJointBrake.go(istSpeed);
                oJointMover.setSpeed(oJointBrake.getSpeed());
                // do the control
                oJointMover.go();            
            }
            break;

        case eSTATE_MOVE:
            
            // do the control
            oJointMover.go();            
            break;            
    }   // end switch    
    
    // always command angle 
    writeBus();
}

void JointControl2::senseBus()
{
    bool bmove = false;

    // get requests & pass them to the controller
    
    // angle requests
    if (pJointBus->getCO_JCONTROL_ANGLE().checkRequested())
    {
        oJointMover.setAngle(pJointBus->getCO_JCONTROL_ANGLE().getValue());
        bmove = true;
    }
    
    // speed requests
    if (pJointBus->getCO_JCONTROL_SPEED().checkRequested())
    {
        oJointMover.setSpeed(pJointBus->getCO_JCONTROL_SPEED().getValue());
        bmove = true;
    }
    
    // if acceleration requests
    if (pJointBus->getCO_JCONTROL_ACCEL().checkRequested())
    {
        oJointMover.setAccel(pJointBus->getCO_JCONTROL_ACCEL().getValue());
        bmove = true;
    }
    
    // sensed speed (TMP we use sollSpeed)
    istSpeed = pJointBus->getSO_JCONTROL_SPEED().getValue();

    // if move requested -> MOVE
    if (bmove)
        setNextState(eSTATE_MOVE);
    // otherwise -> FREE
    else
        setNextState(eSTATE_FREE);
}

void JointControl2::writeBus()
{
    float sollAngle = oJointMover.getAngle();        // angle requested by this module (float to grant continuity)
    int limitReached = oJointMover.isLimitReached() ? 1:0;    // commanded angle out of joint's range  
    float sollSpeed = oJointMover.getSpeed();        
    
    // command angle
    pJointBus->getCO_JOINT_ANGLE().request(sollAngle);
    
    // inform of control speed
    pJointBus->getSO_JCONTROL_SPEED().setValue(sollSpeed);

    // inform of limit reached
    pJointBus->getSO_JCONTROL_LIMIT_REACHED().setValue(limitReached);

    if (limitReached)            
        LOG4CXX_WARN(logger, "joint limit!");
            
    // inform real speed 
    // TEMP: real position not read yet. 
    if (!ArmConfig::isArmPositionRead())
    {
        // Till then, SOLL angles informed here
        pJointBus->getSO_IST_ANGLE().setValue(sollAngle);
    }
}

void JointControl2::showState()
{
    switch (getState())
    {
        case eSTATE_FREE:
            LOG4CXX_INFO(logger, ">> free");
            break;
                    
        case eSTATE_MOVE:
            LOG4CXX_INFO(logger, ">> move");
            break;
            
    }   // end switch    
}

}