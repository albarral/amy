/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/JointControl.h"
#include "amy/arm/config/ArmConfig.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr JointControl::logger(Logger::getLogger("amy.arm"));

JointControl::JointControl()
{
    benabled = false;
    bconnected = false;
    pJointBus = 0;
    sollAngle = 0;
    limitReached = 0;
}

//JointControl::~JointControl()
//{
//}

void JointControl::init(std::string jointName, Joint& oJoint)
{
    modName = "jcontrol-" + jointName;
    mJoint = &oJoint;
    benabled = true;

    LOG4CXX_INFO(logger, modName << " initialized");      
    LOG4CXX_DEBUG(logger, "joint range= " << mJoint->getLowerLimit() << ", " << mJoint->getUpperLimit());
};

void JointControl::connect(JointBus& oConnectionsJoint)
{
    pJointBus = &oConnectionsJoint;
    bconnected = true;

    LOG4CXX_DEBUG(logger, modName << " connected to bus");      
}

void JointControl::first()
{
    setState(eSTATE_GO);
    setNextState(eSTATE_GO);
    
    // angle = read from ist angle
    
    log4cxx::NDC::push(modName);   	
}
                    
void JointControl::loop()
{
    senseBus();
    
    updateState();
    
    oClick.read();
    oClick.start();
      
    switch (getState())
    {
        case eSTATE_GO:            

            doSpeed2Angle();
            break;
    }   // end switch    
    
    // core behaviour: must always write commands 
    writeBus();
}

void JointControl::senseBus()
{
    // get last commanded SOLL angle 
    sollAngle = pJointBus->getCO_JOINT_ANGLE().getValue();
    
    // get requested joint speed
    if (pJointBus->getCO_JCONTROL_SPEED().checkRequested())
    {
        sollSpeed = pJointBus->getCO_JCONTROL_SPEED().getValue();
        // convert it for easier handling
        sollSpeed_ms = sollSpeed/1000.0;
    }
}

void JointControl::writeBus()
{
    // send soll angle
    pJointBus->getCO_JOINT_ANGLE().request(sollAngle);
    // if changed, show it
//    if (sollAngle != prevSollAngle)
//    {
//        LOG4CXX_INFO(logger, "angle=" << (int)sollAngle);
//        prevSollAngle = sollAngle;
//    }
    
    // inform limit reached
    pJointBus->getSO_LIMIT_REACHED().setValue(limitReached);
            
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

void JointControl::doSpeed2Angle()
{
    if (sollSpeed_ms == 0)
        return;
    
    sollAngle += (float)(sollSpeed_ms*oClick.getMillis());      
    
    // limit angle to joint's range
    if (sollAngle > mJoint->getUpperLimit())
    {
        LOG4CXX_WARN(logger, "upper limit!");
        sollAngle = mJoint->getUpperLimit();
        limitReached = 1;
    }
    else if (sollAngle < mJoint->getLowerLimit())
    {
        LOG4CXX_WARN(logger, "lower limit!");
        sollAngle = mJoint->getLowerLimit();
        limitReached = -1;
    }
    else
        limitReached = 0;
}


}