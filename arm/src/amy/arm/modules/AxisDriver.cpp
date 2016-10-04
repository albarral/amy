/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include "log4cxx/ndc.h"

#include "amy/arm/modules/AxisDriver.h"
#include "amy/arm/modules/JointMover.h"
#include "amy/arm/util/ArmMath.h"

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
    accel = 0;
    Kaccel = 4.0;
}

//AxisDriver2::~AxisDriver2()
//{
//}

void AxisDriver::init(int dTol, int vApproach, float vTol, MovementControl& oMovementControl)
{
    // valid params
    if (dTol > 0 && vApproach > 0 && vTol > 0.0)
    {
        this->dTol = dTol;
        this->vTol = vTol;
        this->vApproach = vApproach;
        vApproachTol = vTol * vApproach;            
        pMovementControl = &oMovementControl;            
        benabled = true;
        
        LOG4CXX_INFO(logger, modName << " initialized");                  
        LOG4CXX_DEBUG(logger, "dTol=" << dTol << ", vApproach=" << vApproach << ", speed tolerance=" << vTol);      
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
    
    log4cxx::NDC::push(modName);   	
}
                    
// performs a cyclic wave movement of the elbow
void AxisDriver::loop()
{
    float dBrake, resolution, dApproach;
    
    senseBus();

    // measure arm distance to target
    float dist = targetPos - istPos;
    float absDist = fabs(dist);

    // check new move requests
    if (bnewRequest)
    {
        newMove(absDist);    
        // reset blocked time 
        blockedTime = 0;
        bnewRequest = false;        
    }
    // if much time blocked -> done
    else if (blockedTime > 5)
        setState(eSTATE_DONE);
    
    // skip if done state
    if (getState() == eSTATE_DONE)
        return;
    
    // TRANSITIONS ...
    switch (getState())
    {
        case eSTATE_DRIVE:

            // to react with enough anticipation (even in worst case) 
            // approach distance considers brake distance and movement resolution
            dBrake = ArmMath::computeBrakeDistance(sollSpeed, accel0);
            resolution = ArmMath::getMovementResolution(fabs(sollSpeed), getFrequency());
            dApproach = dBrake + resolution;
            // limit it on tolerance
            if (dApproach < dTol) 
                dApproach = dTol;
            
            // near to target -> approach
            if (absDist < dApproach)
                setState(eSTATE_APPROACH);                         
            break;
                        
        case eSTATE_APPROACH:

            // in target -> arrived
            if (absDist < dTol)
                setState(eSTATE_ARRIVED);
            break;
    }   // end switch        
            
    
    if (isStateChanged())
        showState();
            
    // ACTIONS
    switch (getState())
    {
        case eSTATE_DRIVE:

            // far from target -> drive
            setDriveSpeed(dist);            
            controlSpeed();                
            break;
                        
        case eSTATE_APPROACH:

            setApproachSpeed(dist);
            controlSpeed();
            break;

        case eSTATE_ARRIVED:
       
            // in target -> done
            doArrived();
            setState(eSTATE_DONE);                                
            break;
    }   // end switch        
    
    // executed whenever state not DONE
    writeBus();
    LOG4CXX_INFO(logger, "out " << JointMover::getSymbol4Action(outAction) << " , ist = " << istPos);
    //LOG4CXX_INFO(logger, " \t \t \t dBrake = " << dBrake << " - resolution = " << resolution << " - accel = " << accel);
}


// starts new move
void AxisDriver::newMove(float absdist)
{
    // set speed according to central movement time
    vDrive = absdist / pMovementControl->getTime4Move();
    vDriveTol = vDrive * vTol;
    // use central acceleration
    accel0 = pMovementControl->getAccel();
    setState(eSTATE_DRIVE);        
    LOG4CXX_INFO(logger, "target = " << targetPos);  
    LOG4CXX_INFO(logger, "ist = " << istPos);
    LOG4CXX_INFO(logger, "v = " << vDrive);  
    LOG4CXX_INFO(logger, "a0 = " << accel0);  
}

// increase blocked time
void AxisDriver::blockedMove()
{
    blockedTime++;
}

void AxisDriver::setDriveSpeed(float dist)
{
    targetSpeed =  (dist > 0.0) ? vDrive : -vDrive;
    speedTol = vDriveTol;
}

void AxisDriver::setApproachSpeed(float dist)
{
    int vCruise;
    // use lowest speed    
    if (vDrive > vApproach)
    {
        vCruise = vApproach;
        speedTol = vApproachTol;
    }
    else
    {
        vCruise = vDrive;
        speedTol = vDriveTol;        
    }
    
    targetSpeed =  (dist > 0.0) ? vCruise : -vCruise;    
}

// gets the proper actions to reach the target speed
void AxisDriver::controlSpeed()
{    
    // compare target and real speeds
    float difSpeed = targetSpeed - sollSpeed;    
    
    // push joint to reach target speed
    if (fabs(difSpeed) > speedTol)
    {
        // adjust acceleration (limiting it)
        accel = Kaccel*fabs(difSpeed);
        if (accel > accel0)
            accel = accel0;
        
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