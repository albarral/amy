/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include "log4cxx/ndc.h"

#include "amy/arm/modules/AxisDriver.h"
#include "amy/arm/modules/JointMover.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AxisDriver::logger(Logger::getLogger("amy.arm"));

AxisDriver::AxisDriver()
{
    benabled = false;
    modName = "AxisDriver";
    
    bconnected = false;
    pBus = 0;
    pJointBus = 0;
    targetPos = 0;  // TEMPORAL
}

//AxisDriver::~AxisDriver()
//{
//}

//int dNear, int dTol, int vHigh, int vLow, float tolerance
void AxisDriver::init(int dNear, int dTol, int vHigh, int vLow, float tolerance)
{
    // valid params
    if (dNear > 0 && dTol > 0 && vHigh > 0 && vLow > 0 && dNear > dTol && tolerance > 0.0)
    {
        this->dNear = dNear;
        this->dTol = dTol;
        this->vHigh = vHigh;
        this->vLow = vLow;
        this->speedTolerance = tolerance;
        tolvHigh = tolerance * vHigh;    
        tolvLow = tolerance * vLow;
        benabled = true;
        
        LOG4CXX_INFO(logger, modName << " initialized");                  
        LOG4CXX_DEBUG(logger, "dNear=" << dNear << ", dTol=" << dTol << ", vHigh=" << vHigh << ", vLow=" << vLow << ", speed tolerance=" << tolerance);      
    }
    // invalid params
    else
    {
        LOG4CXX_ERROR(logger, modName << " initialization FAILED");      
    }
};

void AxisDriver::connect(ArmBus& oBus)
{
    pBus = &oBus;
    bconnected = true;
    selectBusJoint();
    
    LOG4CXX_DEBUG(logger, modName << " connected to bus");      
}

void AxisDriver::first()
{
    // start at done
    setState(eSTATE_DONE);
    setNextState(eSTATE_DONE);
    
    log4cxx::NDC::push(modName);   	
}
                    
// performs a cyclic wave movement of the elbow
void AxisDriver::loop()
{
    senseBus();

    if (updateState())
        showState();
        
    // if done -> do nothing 
    if (getState() == eSTATE_DONE)
        return;

    // otherwise, control arm
    float dist = targetPos - istPos;
    float absDist = fabs(dist);
    
    switch (getState())
    {
        case eSTATE_DRIVE:
            
            // not in target -> drive joint
            if (absDist > dTol && blockedTime<5)
                doDrive(dist, absDist);
            // in target -> arrived
            else 
            {
                doArrived();
                setNextState(eSTATE_ARRIVED);
            }
            break;
                        
        case eSTATE_ARRIVED:
       
            // in target -> done
            doArrived();
            setNextState(eSTATE_DONE);                
                
            break;
    }   // end switch        
    
    writeBus();
    LOG4CXX_INFO(logger, "out: " << outAction << " - ist = " << istPos);
}


// starts new move
void AxisDriver::newMove()
{
    // reset blocked time and drive 
    blockedTime = 0;
    setNextState(eSTATE_DRIVE);   
    LOG4CXX_INFO(logger, "target = " << targetPos);  
    LOG4CXX_INFO(logger, "ist = " << istPos);
}

// increase blocked time
void AxisDriver::blockedMove()
{
    blockedTime++;
}

// move joint to target position at proper speed (with a tolerance)
void AxisDriver::doDrive(float dist, float absDist)
{    
    int vCruise, tolvCruise;
        
    // far target -> high speed
    if (absDist > dNear)
    {
        vCruise = vHigh;
        tolvCruise = tolvHigh;
    }
    // near target -> low speed
    else if (absDist > dTol)
    {
        vCruise = vLow;
        tolvCruise = tolvLow;
    }
    
    // deduce target speed (implies direction)
    int targetSpeed = (dist > 0.0) ? vCruise : -vCruise;
    // compare target and real speeds
    int difSpeed = targetSpeed - (int)istSpeed;    
    
    // push joint to reach target speed
    if (fabs(difSpeed) > tolvCruise)
    {
        if (difSpeed > 0)
            outAction = JointMover::eMOV_PUSH_FRONT;
        else 
            outAction = JointMover::eMOV_PUSH_BACK;        
    }
    // if reached (with tolerance), keep joint speed
    else
        outAction = JointMover::eMOV_KEEP;
}

// stop joint 
void AxisDriver::doArrived()
{
    outAction = JointMover::eMOV_STOP;
}

void AxisDriver::showState()
{
    switch (getState())
    {
        case eSTATE_DONE:
            LOG4CXX_INFO(logger, ">> done");
            break;
                        
        case eSTATE_ARRIVED:
            LOG4CXX_INFO(logger, ">> arrived");
            break;

        case eSTATE_DRIVE:
            LOG4CXX_INFO(logger, ">> drive");
            break;
    }   // end switch    
}


}