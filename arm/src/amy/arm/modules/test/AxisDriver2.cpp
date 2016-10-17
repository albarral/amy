/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include "log4cxx/ndc.h"

#include "amy/arm/modules/test/AxisDriver2.h"
#include "amy/arm/util/ArmMath.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AxisDriver2::logger(Logger::getLogger("amy.arm"));

AxisDriver2::AxisDriver2()
{
    benabled = false;
    modName = "AxisDriver2";
    
    bconnected = false;
    pBus = 0;
    pJointBus = 0;
    targetPos = 0;  // TEMPORAL
    accel = 0;
    // params default    
    Kaccel = 4.0;
    resolution = 1;
    time4move = 2.0;
}

//AxisDriver22::~AxisDriver22()
//{
//}

void AxisDriver2::init(float tolPos, float tolSpeed, int vApproach, MovementControl& oMovementControl)
{
    // valid params
    if (tolPos > 0 && vApproach > 0 && tolSpeed > 0.0)
    {
        this->tolPos = tolPos;
        this->tolSpeed = tolSpeed;
        this->vApproach = vApproach;
        pMovementControl = &oMovementControl;            
        benabled = true;
        
        LOG4CXX_INFO(logger, modName << " initialized");                  
        LOG4CXX_DEBUG(logger, "tolPos=" << tolPos << ",tolSpeed=" << tolSpeed << ", vApproach=" << vApproach);      
    }
    // invalid params
    else
    {
        LOG4CXX_ERROR(logger, modName << " initialization FAILED");      
    }
};

void AxisDriver2::connect(ArmBus& oBus)
{
    pBus = &oBus;
    bconnected = true;
    selectBusJoint();
    
    LOG4CXX_DEBUG(logger, modName << " connected to bus");      
}

void AxisDriver2::first()
{
    // start at done
    bnewRequest = false;
    setState(eSTATE_DONE);
    
    log4cxx::NDC::push(modName);   	
}
                    
// performs a cyclic wave movement of the elbow
void AxisDriver2::loop()
{
    float resolution, dApproach;
    
    senseBus();

    // measure arm distance to target
    float dist = targetPos - istPos;
    float absDist = fabs(dist);

    // check new move requests
    if (bnewRequest)
    {
        bnewRequest = false;        
        newMove(absDist);    
        // reset blocked time 
        blockedTime = 0;        
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

            // compute the approach distance so that we have enough space to brake
            // the approach distance must also account for the movement's resolution at present speed
            resolution = ArmMath::getMovementResolution(fabs(sollSpeed), getFrequency());
            dApproach = dBrake + resolution;
            // never allow it go under the position tolerance
            if (dApproach < posTol) 
                dApproach = posTol;
            
            // near to target -> approach
            if (absDist < dApproach)
                setState(eSTATE_APPROACH);                         
            break;
                        
        case eSTATE_APPROACH:

            // in target -> arrived
            if (absDist < posTol)
                setState(eSTATE_ARRIVED);
            break;

        case eSTATE_ARRIVED:
       
            // in target -> done
            if ((int)sollSpeed == 0)
                setState(eSTATE_DONE);                                
            break;
    }   // end switch        
            
    
    if (isStateChanged())
        showState();
            
    // ACTIONS
    switch (getState())
    {
        case eSTATE_DRIVE:

            // drive at high speed
            updateTargetSpeed(vDrive, dist);
            break;
                        
        case eSTATE_APPROACH:

            // (normal case) approach at lower speed
            if (vDrive > vApproach) 
               updateTargetSpeed(vApproach, dist);
            // (special case) if drive speed already lower, use it for approach
            else
                updateTargetSpeed(vDrive, dist);
            break;

        case eSTATE_ARRIVED:
       
            // stop joint 
            updateTargetSpeed(0.0, dist);
            break;
    }   // end switch        
    
    // compute proper acceleration 
    controlSpeed();                
    // and send it to bus
    writeBus();
    LOG4CXX_INFO(logger, "out accel = " << accel << " \t ist = " << istPos);
    //LOG4CXX_INFO(logger, " \t \t \t dBrake = " << dBrake << " - resolution = " << resolution << " - accel = " << accel);
}


// starts new move
void AxisDriver2::newMove(float absdist)
{
    // compute next things for the move ...
    
    // the speed needed to do it in the required time
    if (time4move > 0.0)
        vDrive = absdist / time4move;

    // the distance needed to brake from maximum speed using the maximum acceleration
    dBrake = ArmMath::computeBrakeDistance(vDrive, maxAccel);

    // the position tolerance allowed for the move
    updatePosTolerance(absdist);

    setState(eSTATE_DRIVE);        
    LOG4CXX_INFO(logger, "target = " << targetPos);  
    LOG4CXX_INFO(logger, "ist = " << istPos);
    LOG4CXX_INFO(logger, "v = " << vDrive);  
    LOG4CXX_INFO(logger, "a = " << maxAccel);  
    LOG4CXX_INFO(logger, "dBrake = " << dBrake);  
}

// increase blocked time
void AxisDriver2::blockedMove()
{
    blockedTime++;
}

void AxisDriver2::updateTargetSpeed(float speed, float dist)
{
    float absSpeed = fabs(speed);
    targetSpeed =  (dist > 0.0) ? absSpeed : -absSpeed;
    speedTol = tolSpeed * absSpeed;  
}

// gets the proper acceleration to reach the target speed
void AxisDriver2::controlSpeed()
{    
    // compute speed error
    float difSpeed = targetSpeed - sollSpeed;        
    // compute acceleration to reach target speed 
    accel = Kaccel*difSpeed;
        
    // keep accel under limits
    if (fabs(accel) > maxAccel)        
        accel = (accel > 0 ? maxAccel : -maxAccel);
}

void AxisDriver2::updatePosTolerance(float dist)
{
    posTol = fabs(dist) * tolPos;    
    // always keep it above the minimal resolution
    if (posTol < resolution)
        posTol = resolution;
}

void AxisDriver2::showState()
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