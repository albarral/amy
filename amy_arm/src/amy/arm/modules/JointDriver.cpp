/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/JointDriver.h"
#include "amy/core/robot/Joint.h"
#include "amy/arm/move/JointAccelerator.h"

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

void JointDriver::init(Arm& oArm, ArmConfig& oArmConfig)
{
    Joint* pJoint = oArm.getJointByType(targetJoint);
    lowLimit = pJoint->getLowerLimit();
    highLimit = pJoint->getUpperLimit();
    brakeAccel = oArmConfig.getBrakeAccel();
    benabled = true;
    LOG4CXX_INFO(logger, modName << " initialized");      
    LOG4CXX_DEBUG(logger, "joint range= " << pJoint->getLowerLimit() << ", " << pJoint->getUpperLimit());
};


void JointDriver::first()
{    
    setState(JointDriver::eSTATE_DONE);
    setNextState(JointDriver::eSTATE_DONE);
  
    oJointAccelerator.reset();
    log4cxx::NDC::push(modName);   	
}
                    
void JointDriver::loop()
{    
    senseBus();

    int state = getState();

    // if no requests & move done -> nothing to do
    if (!baccel && state == eSTATE_DONE)
        return; 
    // otherwise, move someway
    else
    {
        // if accel requested -> MOVE
        if (baccel)
        {
            if (state != eSTATE_MOVE)
            {
                setNextState(eSTATE_MOVE);
                // if coming from DONE, store angle 
                if (state == eSTATE_DONE)
                    oJointAccelerator.touch(angle);                      
            }
        }
        // if no accel request -> BRAKE        
        else
            setNextState(eSTATE_BRAKE);            
    }
        
    if (updateState())   
        showState();
              
    switch (getState())
    {
        case eSTATE_BRAKE:            

            // if joint is moving, brake it
            if (oJointAccelerator.getSpeed() != 0.0)
            {
                angle = oJointAccelerator.brake(angle, brakeAccel);
                angle = limitAngle(angle);
                //LOG4CXX_INFO(logger, oJointMove.toString());
            }
            // otherwise -> DONE
            else
            {
                setNextState(eSTATE_DONE);            
                updateState();
                showState();
            }
                
            break;

        case eSTATE_MOVE:
            
            // do the control
            angle = oJointAccelerator.move(angle, accel);            
            angle = limitAngle(angle);
            //LOG4CXX_INFO(logger, oJointMove.toString());
            break;            
    }   // end switch    
    
    // always command angle 
    writeBus();    
}

void JointDriver::senseBus()
{
    // sense angle
    angle = pJointBus->getCO_JOINT_ANGLE().getValue();
        
    // accel requested 
    if (pJointBus->getCO_JOINT_ACCEL().checkRequested())
    {
        accel = pJointBus->getCO_JOINT_ACCEL().getValue();
        baccel = true;
    }    
    else
        baccel = false;
    
    // inform real speed 
    // TEMP: real position not read yet. Should be done in another module
    // Till then, SOLL angles informed here
    pJointBus->getSO_IST_ANGLE().setValue(angle);    
}

void JointDriver::writeBus()
{
    float sollSpeed = oJointAccelerator.getSpeed();        
    int state = getState();
    
    // CO commands ...
    // joint angle
    pJointBus->getCO_JOINT_ANGLE().request(angle);
    
    // SO informations ...
    // driver state
    pJointBus->getSO_DRIVER_STATE().setValue(state);
    // control speed
    pJointBus->getSO_JOINT_SPEED().setValue(sollSpeed);
    // limit reached
    pJointBus->getSO_JOINT_LIMIT_REACHED().setValue(limitReached);

    if (limitReached != 0)            
        LOG4CXX_WARN(logger, "joint limit!");            
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
        case eSTATE_DONE:
            LOG4CXX_INFO(logger, ">> done");
            break;

        case eSTATE_BRAKE:
            LOG4CXX_INFO(logger, ">> brake");
            break;
                    
        case eSTATE_MOVE:
            LOG4CXX_INFO(logger, ">> move");
            break;
            
    }   // end switch    
}

}