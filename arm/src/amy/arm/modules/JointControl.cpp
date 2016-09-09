/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/JointControl.h"

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
    limitBroken = 0;
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
    
    if (sollAngle != prevSollAngle)
    {
        writeBus();
        prevSollAngle = sollAngle;
    }
}

void JointControl::senseBus()
{
    // get last commanded SOLL angle (CO_JOINT_ANGLE) 
    sollAngle = pJointBus->getCO_JOINT_ANGLE().getValue();
    
    // get speed request (CO_SOLL_SPEED) 
    if (pJointBus->getCO_JCONTROL_SPEED().checkRequested())
    {
        sollSpeed = pJointBus->getCO_JCONTROL_SPEED().getValue();
        sollSpeed_ms = sollSpeed/1000.0;
    }
}

void JointControl::writeBus()
{
    // request new SOLL angle (CO_SOLL_ANGLE)
    pJointBus->getCO_JOINT_ANGLE().request(sollAngle);
    LOG4CXX_DEBUG(logger, "angle=" << (int)sollAngle);
    
    // update real IST speed (SO_REAL_SPEED)
    // TEMPORAL !!! 
    // We put the SOLL speed here instead of the IST speed. 
    // That's because we are not reading the IST angles yet, needed for its computation.
    pJointBus->getSO_REAL_SPEED().setValue(sollSpeed);
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
        limitBroken = 1;
    }
    else if (sollAngle < mJoint->getLowerLimit())
    {
        LOG4CXX_WARN(logger, "lower limit!");
        sollAngle = mJoint->getLowerLimit();
        limitBroken = -1;
    }
    else
        limitBroken = 0;
}


}