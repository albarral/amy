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
    lowLimit = highLimit = 0;
    limitReached = false;
    brakeAccel = 0.0;
}

//JointControl2::~JointControl2()
//{
//}

void JointControl2::init(Arm& oArm)
{
    Joint* pJoint = oArm.getJointByName(jointName);
    lowLimit = pJoint->getLowerLimit();
    highLimit = pJoint->getUpperLimit();
    ArmConfig oArmConfig;
    brakeAccel = oArmConfig.getBrakeAccel();
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
              
    switch (getState())
    {
        case eSTATE_FREE:            

            // if joint is moving, brake it
            if (oJointMover.getSpeed() != 0.0)
            {
                // do the control
                angle = oJointMover.brake(brakeAccel, angle);
                angle = limitAngle(angle);
                LOG4CXX_INFO(logger, oJointMover.toString());
            }
            // otherwise keep joint iddle
            else
                oJointMover.iddle();
                
            break;

        case eSTATE_MOVE:
            
            // do the control
            angle = oJointMover.move(accel, angle);            
            angle = limitAngle(angle);
            LOG4CXX_INFO(logger, oJointMover.toString());
            break;            
    }   // end switch    
    
    // always command angle 
    writeBus();
    
}

void JointControl2::senseBus()
{
    bool bmove = false;

    // sense angle
    angle = pJointBus->getCO_JOINT_ANGLE().getValue();
        
    // if acceleration requests
    if (pJointBus->getCO_JCONTROL_ACCEL().checkRequested())
    {
        accel = pJointBus->getCO_JCONTROL_ACCEL().getValue();
        bmove = true;
    }
          
    // if move requested -> MOVE
    if (bmove)
        setNextState(eSTATE_MOVE);
    // otherwise -> FREE
    else
        setNextState(eSTATE_FREE);
}

void JointControl2::writeBus()
{
    float sollSpeed = oJointMover.getSpeed();        
    
    // command angle
    pJointBus->getCO_JOINT_ANGLE().request(angle);
    
    // inform of control speed
    pJointBus->getSO_JCONTROL_SPEED().setValue(sollSpeed);

    // inform of limit reached
    pJointBus->getSO_JCONTROL_LIMIT_REACHED().setValue(limitReached);

    if (limitReached != 0)            
        LOG4CXX_WARN(logger, "joint limit!");
            
    // inform real speed 
    // TEMP: real position not read yet. 
    if (!ArmConfig::isArmPositionRead())
    {
        // Till then, SOLL angles informed here
        pJointBus->getSO_IST_ANGLE().setValue(angle);
    }
}

float JointControl2::limitAngle(float value)
{
    float angle;
    if (value < lowLimit) 
    {
        angle = lowLimit;
        limitReached = -1;
    }
    else if (value > highLimit)
    {
        angle = highLimit;
        limitReached = 1;
    }
    else 
    {
        angle = value;        
        limitReached = 0;
    }    
    return angle;
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