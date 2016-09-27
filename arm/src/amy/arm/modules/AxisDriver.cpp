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
    modName = "AxisDriver2";
    
    bconnected = false;
    pBus = 0;
    pJointBus = 0;
    targetPos = 0;  // TEMPORAL
}

//AxisDriver2::~AxisDriver2()
//{
//}

void AxisDriver::init(int dTol, int vApproach, float tolerance, MovementControl& oMovementControl)
{
    // valid params
    if (dTol > 0 && vApproach > 0 && tolerance > 0.0)
    {
        this->dTol = dTol;
        this->tolerance = tolerance;
        this->vApproach = vApproach;
        vApproachTol = tolerance * vApproach;            
        pMovementControl = &oMovementControl;            
        benabled = true;
        
        LOG4CXX_INFO(logger, modName << " initialized");                  
        LOG4CXX_DEBUG(logger, "dTol=" << dTol << ", vApproach=" << vApproach << ", speed tolerance=" << tolerance);      
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
    bnewRequest = false;
    setState(eSTATE_DONE);
    setNextState(eSTATE_DONE);
    
    log4cxx::NDC::push(modName);   	
}
                    
// performs a cyclic wave movement of the elbow
void AxisDriver::loop()
{
    senseBus();

    // measure arm distance to target
    float dist = targetPos - istPos;
    float absDist = fabs(dist);

    if (bnewRequest)
    {
        newMove(absDist);
        bnewRequest = false;        
    }

    if (blockedTime > 5)
        setNextState(eSTATE_DONE);
    
    if (updateState())
        showState();
        
    // if done -> do nothing 
    if (getState() == eSTATE_DONE)
        return;

    // compute brake distance needed at present speed (dbrake = v²/2a)
    int dBrake = istSpeed*istSpeed/(2*pMovementControl->getAccel());
    
    switch (getState())
    {
        case eSTATE_DRIVE:
            
            // far from target -> drive
            if (absDist > dBrake)
            {
                setDriveSpeed(dist);
                controlSpeed();
            }
            // near to target -> approach
            else if (absDist > dTol)
            {
                setApproachSpeed(dist);
                controlSpeed();
                setNextState(eSTATE_APPROACH);                
            }
            // in target -> arrived
            else 
            {
                doArrived();
                setNextState(eSTATE_ARRIVED);
            }
            break;
                        
        case eSTATE_APPROACH:
            
            // near to target -> approach
            if (absDist > dTol)
            {
                setApproachSpeed(dist);
                controlSpeed();
            }
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
void AxisDriver::newMove(float absdist)
{
    // reset blocked time 
    blockedTime = 0;
    // get speed needed to execute movement in required time
    vDrive = absdist / pMovementControl->getTime4Move();
    vDriveTol = tolerance * vDrive;
    setNextState(eSTATE_DRIVE);        
    LOG4CXX_INFO(logger, "target = " << targetPos);  
    LOG4CXX_INFO(logger, "ist = " << istPos);
    LOG4CXX_INFO(logger, "v = " << vDrive);  
}

// increase blocked time
void AxisDriver::blockedMove()
{
    blockedTime++;
}

void AxisDriver::setDriveSpeed(int dist)
{
    targetSpeed =  (dist > 0.0) ? vDrive : -vDrive;
    speedTol = vDriveTol;
}

void AxisDriver::setApproachSpeed(int dist)
{
    targetSpeed =  (dist > 0.0) ? vApproach : -vApproach;
    speedTol = vApproachTol;
}

// gets the proper actions to reach the target speed
void AxisDriver::controlSpeed()
{    
    // compare target and real speeds
    float difSpeed = targetSpeed - istSpeed;    
    
    // push joint to reach target speed
    if (fabs(difSpeed) > speedTol)
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

        case eSTATE_APPROACH:
            LOG4CXX_INFO(logger, ">> approach");
            break;

        case eSTATE_DRIVE:
            LOG4CXX_INFO(logger, ">> drive");
            break;
    }   // end switch    
}


}