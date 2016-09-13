/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include "log4cxx/ndc.h"

#include "amy/arm/modules/JointMover.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr JointMover::logger(Logger::getLogger("amy.arm"));

JointMover::JointMover()
{
    benabled = false;
    targetDirection = 0;
    sollSpeed = 0;
    
    bconnected = false;
    pJointBus = 0;
}

//JointMover::~JointMover()
//{
//}

void JointMover::init(std::string jointName, ParamsJointMover& oParamsJointMover)
{
    // all params must be positive
    if (oParamsJointMover.getAccel() <= 0 || 
       oParamsJointMover.getBrakeAccel() <= 0)
        return;

    modName = "jmover-" + jointName;
    accel = oParamsJointMover.getAccel();
    accel_ms = (float)this->accel/1000;
    brakeAccel = oParamsJointMover.getBrakeAccel();
    brakeAccel_ms = (float)this->brakeAccel/1000;
    benabled = true;

    LOG4CXX_INFO(logger, modName << " initialized");      
    LOG4CXX_DEBUG(logger, "accel=" << accel << ", brakeAccel=" << brakeAccel);      
};

void JointMover::connect(JointBus& oConnectionsJoint)
{
    pJointBus = &oConnectionsJoint;
    bconnected = true;

    LOG4CXX_DEBUG(logger, modName << " connected to bus");      
}

void JointMover::first()
{
    setState(eSTATE_AUTOBRAKE);
    setNextState(eSTATE_AUTOBRAKE);
    
    log4cxx::NDC::push(modName);   	
}
                    
void JointMover::loop()
{
    senseBus();
    
    if (updateState())
        showState();
    
    oClick.read();
    oClick.start();
      
    switch (getState())
    {
        case eSTATE_AUTOBRAKE:            
            
            if (sollSpeed != 0.0)
                doBrake();    
            break;

        case eSTATE_KEEP:
            
            // nothing done
            break;

        case eSTATE_ACCEL:            

            doAccelerate();
            break;            
    }   // end switch    
    
    writeBus();
}


// sense bus requests
void JointMover::senseBus()
{
    // always work with last commanded speed to JControl
    // CO_JCONTROL_SPEED
    sollSpeed = pJointBus->getCO_JCONTROL_SPEED().getValue();
    
    // CO_JMOVER_ACTION
    if (pJointBus->getCO_JMOVER_ACTION().checkRequested())
        processRequest(pJointBus->getCO_JMOVER_ACTION().getValue());
    // if no requests -> auto brake
    else
        setNextState(eSTATE_AUTOBRAKE);
}


// send requests through bus
void JointMover::writeBus()
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


// process action requests (from bus)
void JointMover::processRequest(int reqCommand)
{
    LOG4CXX_DEBUG(logger, "action requested - " << reqCommand);      

    switch (reqCommand)
    {
        // accelerate to positive direction (right or up) 
        case eMOV_PUSH_FRONT:
            targetDirection = 1;
            setNextState(eSTATE_ACCEL);
            break;
            
        // accelerate to negative direction (left or down) 
        case eMOV_PUSH_BACK:
            targetDirection = -1;
            setNextState(eSTATE_ACCEL);
            break;
            
        // keeps present speed
        case eMOV_KEEP:
            setNextState(eSTATE_KEEP);
            break;
            
        default:
            LOG4CXX_INFO(logger, "> unknown request");
            break;
    }    
}


// Change speed in the target direction.
void JointMover::doAccelerate()
{
    sollSpeed += (float)(targetDirection*accel_ms*oClick.getMillis());
}

// Decrease speed to 0
void JointMover::doBrake()
{
    // brake in the opposite direction of present speed
    int brakeDirection = (sollSpeed > 0.0) ? -1 : 1;
    float change = (float)(brakeDirection*brakeAccel_ms*oClick.getMillis());

    // update speed
    if (fabs(change) < fabs(sollSpeed))
        sollSpeed += change;
    // or set it to 0 if overdecreased 
    else
        sollSpeed = 0;
}

void JointMover::showState()
{
    switch (getState())
    {
        case eSTATE_AUTOBRAKE:
            LOG4CXX_INFO(logger, ">> autobrake");
            break;
                    
        case eSTATE_KEEP:
            LOG4CXX_INFO(logger, ">> keep");
            break;

        case eSTATE_ACCEL:
            LOG4CXX_INFO(logger, ">> accel");
            break;
            
    }   // end switch    
}
}