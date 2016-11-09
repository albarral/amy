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
    setState(JointControl2::STATE_ON);
    setNextState(JointControl2::STATE_ON);
        
    log4cxx::NDC::push(modName);   	
}
                    
void JointControl2::loop()
{
    senseBus();
              
    // do the control
    oJointMover.go();
    
    // always command angle 
    writeBus();
}

void JointControl2::senseBus()
{
    // if angle requested, set it
    if (pJointBus->getCO_JCONTROL_ANGLE().checkRequested())
        oJointMover.setAngle(pJointBus->getCO_JCONTROL_ANGLE().getValue());
    
    // if speed requested, set it
    if (pJointBus->getCO_JCONTROL_SPEED().checkRequested())
        oJointMover.setSpeed(pJointBus->getCO_JCONTROL_SPEED().getValue());
    
    // if acceleration requested, set it
    if (pJointBus->getCO_JCONTROL_ACCEL().checkRequested())
        oJointMover.setAccel(pJointBus->getCO_JCONTROL_ACCEL().getValue());
}

void JointControl2::writeBus()
{
    float sollAngle = oJointMover.getAngle();        // angle requested by this module (float to grant continuity)
    int limitReached = oJointMover.isLimitReached() ? 1:0;    // commanded angle out of joint's range  
    float sollSpeed = oJointMover.getSpeed();        
    
    // command soll angle
    pJointBus->getCO_JOINT_ANGLE().request(sollAngle);
    
    // inform limit reached
    pJointBus->getSO_LIMIT_REACHED().setValue(limitReached);

    if (limitReached)            
        LOG4CXX_WARN(logger, "joint limit!");
            
    // inform real speed 
    // TEMP: real position not read yet. 
    if (!ArmConfig::isRealArmPositionRead())
    {
        // Till then, SOLL speed informed here
        pJointBus->getSO_REAL_SPEED().setValue(sollSpeed);
        // Till then, SOLL angles informed here
        pJointBus->getSO_IST_ANGLE().setValue(sollAngle);
    }
}

}