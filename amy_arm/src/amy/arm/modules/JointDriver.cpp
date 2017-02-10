/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/JointDriver.h"
#include "amy/core/robot/Joint.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr JointDriver::logger(Logger::getLogger("amy.arm"));

JointDriver::JointDriver()
{
    modName = "jdriver";
    lowLimit = highLimit = 0;
    limitReached = false;
    brakeAccel = 0.0;
}

//JointDriver::~JointDriver()
//{
//}

void JointDriver::init(Arm& oArm, AmyArmConfig& oAmyArmConfig)
{
    Joint* pJoint = oArm.getJointByName(jointName);
    lowLimit = pJoint->getLowerLimit();
    highLimit = pJoint->getUpperLimit();
    brakeAccel = oAmyArmConfig.getBrakeAccel();
    benabled = true;
    LOG4CXX_INFO(logger, modName << " initialized");      
    LOG4CXX_DEBUG(logger, "joint range= " << pJoint->getLowerLimit() << ", " << pJoint->getUpperLimit());
};


void JointDriver::first()
{
    setState(JointDriver::eSTATE_FREE);
    setNextState(JointDriver::eSTATE_FREE);
        
    log4cxx::NDC::push(modName);   	
}
                    
void JointDriver::loop()
{    
    senseBus();

    if (updateState())   
        showState();
              
    switch (getState())
    {
        case eSTATE_FREE:            

            // if joint is moving, brake it
            if (oJointMove.getSpeed() != 0.0)
            {
                // do the control
                angle = oJointMove.brake(brakeAccel, angle);
                angle = limitAngle(angle);
                //LOG4CXX_INFO(logger, oJointMove.toString());
            }
            // otherwise keep joint iddle
            else
                oJointMove.iddle();
                
            break;

        case eSTATE_MOVE:
            
            // do the control
            angle = oJointMove.move(accel, angle);            
            angle = limitAngle(angle);
            //LOG4CXX_INFO(logger, oJointMove.toString());
            break;            
    }   // end switch    
    
    // always command angle 
    writeBus();
    
}

void JointDriver::senseBus()
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

void JointDriver::writeBus()
{
    float sollSpeed = oJointMove.getSpeed();        
    
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
    // Till then, SOLL angles informed here
    pJointBus->getSO_IST_ANGLE().setValue(angle);
}

float JointDriver::limitAngle(float value)
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


void JointDriver::showState()
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