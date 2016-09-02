/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/JointMover.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr JointMover::logger(Logger::getLogger("amy.arm"));

JointMover::JointMover()
{
    benabled = false;
    direction = 0;
    targetSpeed = 0;
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
       oParamsJointMover.getCruiseSpeed() <= 0 ||
       oParamsJointMover.getBrakeAccel() <= 0)
        return;

    modName = jointName + "-mover";
    accel = oParamsJointMover.getAccel();
    accel_ms = (float)this->accel/1000;
    brakeAccel = oParamsJointMover.getBrakeAccel();
    brakeAccel_ms = (float)this->brakeAccel/1000;
    cruiseSpeed = oParamsJointMover.getCruiseSpeed();
    benabled = true;

    LOG4CXX_INFO(logger, modName << " initialized");      
    LOG4CXX_DEBUG(logger, "accel=" << accel << ", cruiseSpeed=" << cruiseSpeed << ", brakeAccel=" << brakeAccel);      
};

void JointMover::connect(JointBus& oConnectionsJoint)
{
    pJointBus = &oConnectionsJoint;
    bconnected = true;

    LOG4CXX_DEBUG(logger, modName << " connected to bus");      
}

void JointMover::first()
{
    setState(eSTATE_STOP);
    setNextState(eSTATE_STOP);
    
    log4cxx::NDC::push(modName + "-stop");   	
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
        case eSTATE_ACCEL:
            {
                bool bcruiseReached = accelMovement();

                // if cruise speed reached -> go to KEEP state
                if (bcruiseReached)
                    setNextState(eSTATE_KEEP);
            }
            break;
            
        case eSTATE_BRAKE:
            
            brakeMovement();
            
            if(sollSpeed == 0)
                setNextState(eSTATE_STOP);    

            break;
                    
        case eSTATE_KEEP:
            
            // nothing done
            break;
            
        case eSTATE_STOP:
            
            // abruptly reduces speed to 0
            if(sollSpeed != 0)
                sollSpeed = 0;
            break;
    }   // end switch    
    
    writeBus();
}


// sense bus requests
void JointMover::senseBus()
{
    // CO_JMOVER_SPEED
    if (pJointBus->getCO_JMOVER_SPEED().checkRequested())
        speedRequest(pJointBus->getCO_JMOVER_SPEED().getValue());

    // CO_JMOVER_ACTION
    if (pJointBus->getCO_JMOVER_ACTION().checkRequested())
        actionRequest(pJointBus->getCO_JMOVER_ACTION().getValue());
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
void JointMover::actionRequest(int reqCommand)
{
    LOG4CXX_DEBUG(logger, "action requested - " << reqCommand);      

    int lastValue = direction;
    switch (reqCommand)
    {
        // start movement to the positive direction (right or up) 
        case eMOV_POSITIVE:
            direction = 1;
            // if direction changed, update target speed
            if (direction != lastValue)
                changeTargetSpeed();
            setNextState(eSTATE_ACCEL);
            break;
            
        // start movement to the negative direction (left or down) 
        case eMOV_NEGATIVE:
            direction = -1;
            // if direction changed, update target speed
            if (direction != lastValue)
                changeTargetSpeed();
            setNextState(eSTATE_ACCEL);
            break;

        // start braking until the joint stops        
        case eMOV_BRAKE:
            setNextState(eSTATE_BRAKE);    
            break;
            
        // keeps the present speed
        case eMOV_KEEP:
            setNextState(eSTATE_KEEP);
            break;
            
        // suddenly stops the joint
        case eMOV_STOP:
            setNextState(eSTATE_STOP);    
            break;

        default:
            LOG4CXX_INFO(logger, "> unknown request");
            break;
    }    
}


// process speed requests (from bus)
void JointMover::speedRequest(float value)
{    
    LOG4CXX_DEBUG(logger, "speed requested - " << value);      
    
    // if cruise speed changed, update target speed
    if (cruiseSpeed != value)
    {
        cruiseSpeed = value;
        changeTargetSpeed();
      
        // and jump to ACCEL if now in cruise stage
        if (getState() == eSTATE_KEEP)
            setNextState(eSTATE_ACCEL);
    }
}

void JointMover::changeTargetSpeed()
{
    targetSpeed = direction * cruiseSpeed;    
}

// Increase speed in the proper direction. Returns true if max speed reached.
bool JointMover::accelMovement()
{
    sollSpeed += (float)(direction*accel_ms*oClick.getMillis());

    // limit speed to max value 
    if (abs(sollSpeed)>=cruiseSpeed)
    {
        sollSpeed = (sollSpeed > 0 ? cruiseSpeed : -cruiseSpeed);
        return true;
    }
    else 
        return false;
}

// decrease speed in the proper direction
void JointMover::brakeMovement()
{
    sollSpeed -= (float)(direction*brakeAccel_ms*oClick.getMillis());

    // set speed to 0 when overdecreased 
    if ((direction > 0 && sollSpeed < 0) ||
        (direction < 0 && sollSpeed > 0))
    {
        sollSpeed = 0;
    }
}

void JointMover::showState()
{
    switch (getState())
    {
        case eSTATE_ACCEL:
            LOG4CXX_INFO(logger, ">> accel");
            log4cxx::NDC::pop();	          
            log4cxx::NDC::push(modName + "(accel)");   	
            break;
            
        case eSTATE_BRAKE:
            LOG4CXX_INFO(logger, ">> brake");
            log4cxx::NDC::pop();	          
            log4cxx::NDC::push(modName + "(brake)");   	
            break;
                    
        case eSTATE_KEEP:
            LOG4CXX_INFO(logger, ">> keep");
            log4cxx::NDC::pop();	          
            log4cxx::NDC::push(modName + "(keep)");   	
            break;
            
        case eSTATE_STOP:
            LOG4CXX_INFO(logger, ">> stop");
            log4cxx::NDC::pop();	          
            log4cxx::NDC::push(modName + "(stop)");   	
            break;
    }   // end switch    
}

}