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
    movementDir = 0;
    // params default    
    Kaccel = 4.0;
    Kspeed = 2.0;
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
//        this->vApproach = vApproach;
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

    // measure position error
    dist = targetPos - istPos;
    float absDist = fabs(dist);

    // if new request -> go to DRIVE
    if (bnewRequest)
    {
        bnewRequest = false;        
        blockedTime = 0;        
        jumpTo(eSTATE_DRIVE);
    }
    // if much time blocked -> done
    else if (blockedTime > 5)
        jumpTo(eSTATE_DONE);
    
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
            // protection against rare case where approach distance is smaller than position tolerance
            if (dApproach < posTol) 
                dApproach = posTol;
            
            // near to target -> approach
            if (absDist < dApproach)
                jumpTo(eSTATE_APPROACH);                         
            break;
                        
        case eSTATE_APPROACH:

            // in target -> arrived
            if (absDist < posTol)
                jumpTo(eSTATE_ARRIVED);
            break;

        case eSTATE_ARRIVED:
       
            // in target -> done
            if ((int)sollSpeed == 0)
                jumpTo(eSTATE_DONE);                                
            break;
    }   // end switch        
            
    
    if (isStateChanged())
        showState();
            
    // ACTIONS
    switch (getState())
    {
        case eSTATE_DRIVE:
            
            // drive at high constant speed
            controlAccel();
            break;
                        
        case eSTATE_APPROACH:

            // approach at proportional speed
            controlSpeed();
            controlAccel();
            break;

        case eSTATE_ARRIVED:
       
            // stop joint 
            controlAccel();
            break;
    }   // end switch        
    
    // send commands
    writeBus();
    LOG4CXX_INFO(logger, "accel = " << accel << " \t ist = " << istPos);
    //LOG4CXX_INFO(logger, " \t \t \t dBrake = " << dBrake << " - resolution = " << resolution << " - accel = " << accel);
}


// jump to given state
// and prepare movement
void AxisDriver2::jumpTo(int state)
{
    float vDrive;
         
    switch (state)
    {
        case eSTATE_DRIVE:

            // set movement direction (will be kept till end of movement)
            movementDir = (dist > 0 ? 1: -1);

            // set target speed for drive stage (depends on required time)
            if (time4move > 0.0)
                vDrive = dist / time4move;            
            updateTargetSpeed(vDrive);

            // compute brake distance (given the drive speed and the maximum acceleration)
            dBrake = ArmMath::computeBrakeDistance(fabs(vDrive), maxAccel);

            // set position tolerance for the move
            updatePosTolerance(fabs(dist));
    
            // show data
            showMovementData();            
            break;
                        
        // case eSTATE_APPROACH: nothing computed

        case eSTATE_ARRIVED:
       
            // null target speed
            updateTargetSpeed(0.0);
            break;
    }   
       
    // set state 
    setState(state);     
}

// increase blocked time
void AxisDriver2::blockedMove()
{
    blockedTime++;
}

void AxisDriver2::updateTargetSpeed(float speed)
{
    targetSpeed =  speed;
    // compute speed tolerance
    speedTol = tolSpeed * fabs(speed);  
}

// gets the proper acceleration to reach the target speed
void AxisDriver2::controlSpeed()
{    
    // approach speed proportional to position error
    float vApproach = Kspeed*dist;
        
    // approach speed can only be reduced
    if (fabs(vApproach) < fabs(targetSpeed))        
        targetSpeed = vApproach;
}
       
// gets a proper acceleration given the target speed
void AxisDriver2::controlAccel()
{    
    // acceleration is proportional to speed error
    float difSpeed = targetSpeed - sollSpeed;        
    accel = Kaccel*difSpeed;
        
    // always kept under limits
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

void AxisDriver2::showMovementData()
{
    LOG4CXX_INFO(logger, "target = " << targetPos);  
    LOG4CXX_INFO(logger, "ist = " << istPos);
    LOG4CXX_INFO(logger, "v = " << targetSpeed);  
    LOG4CXX_INFO(logger, "a = " << maxAccel);  
    LOG4CXX_INFO(logger, "dBrake = " << dBrake);      
}

}