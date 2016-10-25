/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include "log4cxx/ndc.h"

#include "amy/arm/modules/AxisDriver3.h"
#include "amy/arm/util/ArmMath.h"
//#include "amy/show/Plot.h"  //  tmp for analysis

using namespace log4cxx;

namespace amy
{
LoggerPtr AxisDriver3::logger(Logger::getLogger("amy.arm"));

AxisDriver3::AxisDriver3()
{
    benabled = false;
    modName = "AxisDriver3";
    
    bconnected = false;
    pBus = 0;
    pJointBus = 0;
    pMovementControl = 0;
    sollAccel = 0;
    moveSign = 0;
}

//AxisDriver32::~AxisDriver32()
//{
//}

void AxisDriver3::init(MovementControl& oMovementControl)
{
    pMovementControl = &oMovementControl;            
    benabled = true;

    LOG4CXX_INFO(logger, modName << " initialized");                  
    LOG4CXX_INFO(logger, oMovementControl.toString());      
};

void AxisDriver3::connect(ArmBus& oBus)
{
    pBus = &oBus;
    bconnected = true;
    selectBusJoint();
    
    LOG4CXX_DEBUG(logger, modName << " connected to bus");      
}

void AxisDriver3::first()
{
    // start at done
    bnewMove = false;
    setState(eSTATE_DONE);
    
    log4cxx::NDC::push(modName);   	
}
                    
// performs a cyclic wave movement of the elbow
void AxisDriver3::loop()
{
    senseBus();

    // in absence or requests
    if (!bnewMove)
    {
        // skip if DONE  
        if (getState() == eSTATE_DONE)
            return;
        // or movement blocked
        else if (blockedTime > 5)
        {
            jumpTo(eSTATE_DONE);
            return;
        }    
    }
        
    // compute distance to target
    dist = computeDistance();

    // HANDLE TRANSITIONS ...
    
    // if new request -> go to DRIVE
    if (bnewMove)
    {
        bnewMove = false;        
        jumpTo(eSTATE_DRIVE);
    }
    
    switch (getState())
    {
        case eSTATE_DRIVE:
            
            // when the drive crosses the approach point -> approach
            if ((moveSign > 0 && dist < approachDist) || 
                (moveSign < 0 && dist > approachDist))
                jumpTo(eSTATE_APPROACH);                         
            break;
                        
        case eSTATE_APPROACH:

            // when the approach crosses the arrival point -> arrived
            if ((moveSign > 0 && dist < arrivalDist) || 
                (moveSign < 0 && dist > arrivalDist))
                jumpTo(eSTATE_ARRIVED);
            break;

        case eSTATE_ARRIVED:
       
            // in target -> done
            if ((int)istSpeed == 0)
                jumpTo(eSTATE_DONE);                                
            break;
    }   // end switch        
            
    
    if (isStateChanged())
        showState();

    // skip if DONE  
    if (getState() == eSTATE_DONE)
        return;
    
    // PERFORM ACTIONS ...
    
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
    
    // record output for analysis
    oRecord.addElement(istSpeed, sollAccel);
    
    // send commands
    writeBus();    
    LOG4CXX_INFO(logger, "\taccel = " << sollAccel << " \t ist = " << istPos);
}


// jump to given state
// and prepare movement
void AxisDriver3::jumpTo(int state)
{         
    switch (state)
    {
        // prepare for new movement
        case eSTATE_DRIVE:

            readParams();
            
            // compute movement direction & speed 
            moveSign = (dist > 0 ? 1: -1);
            setTargetSpeed(driverSpeed * moveSign);

            // the approach & arrival points are also computed (both with same sign as initial distance)
            approachDist = dist*approachFraction;
            arrivalDist = dist*driverTolerance;
            blockedTime = 0;        
            
            // approach protection: the approach point must never be located after the arrival point
            if (fabs(approachDist) < fabs(arrivalDist)) 
                approachDist = arrivalDist;

            // record output for analysis
            oRecord.reset();

            // show data
            showMovementData();            
            break;
                        
        // case eSTATE_APPROACH: nothing computed

        case eSTATE_ARRIVED:
       
            // null target speed
            setTargetSpeed(0.0);
            break;
            
        case eSTATE_DONE:
       
            //Plot::plotRecord(oRecord, 60);
            break;            
    }   
       
    // set state 
    setState(state);     
}

// increase blocked time
void AxisDriver3::blockedMove()
{
    blockedTime++;
}

void AxisDriver3::setTargetSpeed(float speed)
{
    targetSpeed = speed;
}

// updates the target speed in the approach stage
void AxisDriver3::controlSpeed()
{    
    // approach speed proportional to position error
    float approachSpeed = Kspeed*dist;
        
    // the approach speed can never exceed the drive speed
    if (fabs(approachSpeed) > fabs(driverSpeed))        
        approachSpeed = driverSpeed * moveSign;
       
    setTargetSpeed(approachSpeed);
}
       
// gets the proper acceleration to reach the target speed
void AxisDriver3::controlAccel()
{    
    // acceleration is proportional to speed error
    float difSpeed = targetSpeed - istSpeed;        
    sollAccel = Kaccel*difSpeed;
}


void AxisDriver3::readParams()
{
    if (pMovementControl != 0)
    {
        Kaccel = pMovementControl->getKaccelDriver(); 
        Kspeed = pMovementControl->getKspeedDriver(); 
        approachFraction = pMovementControl->getApproachFractionDriver();
        driverTolerance = pMovementControl->getDriverTolerance();
        driverSpeed = pMovementControl->getDriverSpeed();    
    }
}

void AxisDriver3::showState()
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

void AxisDriver3::showMovementData()
{
    LOG4CXX_INFO(logger, "target = " << targetPos);  
    LOG4CXX_INFO(logger, "ist = " << istPos);
    LOG4CXX_INFO(logger, "v = " << targetSpeed);  
    LOG4CXX_INFO(logger, "approachDist = " << approachDist);      
    LOG4CXX_INFO(logger, "arrivedDist = " << arrivalDist);      
}

}