/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include "log4cxx/ndc.h"

#include "amy/arm/modules/JointMover2.h"
#include "amy/arm/config/ArmConfig.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr JointMover2::logger(Logger::getLogger("amy.arm"));

JointMover2::JointMover2()
{
    modName = "jmover2";
    brakeAccel = brakeAccel_ms = 0;
    accel = accel_ms = 0;
    sollSpeed = 0;
}

//JointMover2::~JointMover2()
//{
//}

void JointMover2::init(Arm& oArm)
{
    ArmConfig oArmConfig;
    int brakeAccel = oArmConfig.getBrakeAccel();  
    // all params must be positive
    if (brakeAccel <= 0)
        return;

    this->brakeAccel = brakeAccel;
    brakeAccel_ms = (float)this->brakeAccel/1000;
    benabled = true;

    LOG4CXX_INFO(logger, modName << " initialized");      
    LOG4CXX_DEBUG(logger, "brakeAccel=" << brakeAccel);      
};


void JointMover2::first()
{
    setState(eSTATE_BRAKE);
    setNextState(eSTATE_BRAKE);
    
    log4cxx::NDC::push(modName);   	
}
                    
void JointMover2::loop()
{
    senseBus();
    
    if (updateState())
        showState();
    
    oClick.read();
    oClick.start();
      
    switch (getState())
    {
        case eSTATE_BRAKE:            
            
            if (sollSpeed != 0.0)
                autoBrake();    
            break;

        case eSTATE_ACCEL:            

            doAccelerate();
            break;            
    }   // end switch    
    
    writeBus();
}


// sense bus requests
void JointMover2::senseBus()
{
    // get soll speed (always work from real last commanded speed)
    sollSpeed = pJointBus->getCO_JCONTROL_SPEED().getValue();
                
     // get requested acceleration (any sign)
     if (pJointBus->getCO_JMOVER_ACCELERATION().checkRequested())
     {                  
        accel = pJointBus->getCO_JMOVER_ACCELERATION().getValue();
        accel_ms = accel/1000;
        setNextState(eSTATE_ACCEL);
     }
     // if no requests -> auto brake
     else
        setNextState(eSTATE_BRAKE);         
}


// send requests through bus
void JointMover2::writeBus()
{
    // CO_JCONTROL_SPEED
    pJointBus->getCO_JCONTROL_SPEED().request(sollSpeed);
    
    // just show output changes
    if(sollSpeed != lastOutput)
    {
        LOG4CXX_INFO(logger, "speed = " << (int)sollSpeed);
        lastOutput = sollSpeed;    
    }
}


// Change speed according to the requested acceleration
void JointMover2::doAccelerate()
{
    sollSpeed += (float)(accel_ms*oClick.getMillis());
}

// Decrease speed to 0
void JointMover2::autoBrake()
{
    // brake in the opposite direction of the present speed
    int brakeDirection = (sollSpeed > 0.0) ? -1 : 1;
    float change = (float)(brakeDirection*brakeAccel_ms*oClick.getMillis());

    // update speed 
    if (fabs(change) < fabs(sollSpeed))
        sollSpeed += change;
    // or vanish it if near enough
    else
        sollSpeed = 0;
}

void JointMover2::showState()
{
    switch (getState())
    {
        case eSTATE_BRAKE:
            LOG4CXX_INFO(logger, ">> brake");
            break;
                    
        case eSTATE_ACCEL:
            LOG4CXX_INFO(logger, ">> accel");
            break;
            
    }   // end switch    
}

}