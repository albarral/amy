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

void AxisDriver::init(int dH, int dL, int vDrive, int vApproach, float tolerance)
{
    // valid params
    if (dH > 0 && dL > 0 && vDrive > 0 && vApproach > 0 && dH > dL && tolerance > 0.0)
    {
        this->dH = dH;
        this->dL = dL;
        this->vDrive = vDrive;
        this->vApproach = vApproach;
        vDriveTol = tolerance * vDrive;    
        vApproachTol = tolerance * vApproach;
        benabled = true;
        
        LOG4CXX_INFO(logger, modName << " initialized");                  
        LOG4CXX_DEBUG(logger, "dH=" << dH << ", dL=" << dL << ", vDrive=" << vDrive << ", vApproach=" << vApproach << ", tolerance=" << tolerance);      
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
    setState(eSTATE_ARRIVED);
    setNextState(eSTATE_ARRIVED);
    
    log4cxx::NDC::push(modName);   	
}
                    
// performs a cyclic wave movement of the elbow
void AxisDriver::loop()
{
    senseBus();

    if (updateState())
        showState();
    
    bsendAction = false;
    float dist = targetPos - istPos;
    float absDist = fabs(dist);
    
    switch (getState())
    {
        case eSTATE_DRIVE:
            
            // big dist -> drive
            if (absDist > dH)
            {
                doDrive(dist);
                bsendAction = true;
            }
            // small dist -> approach
            else if (absDist > dL)
                setNextState(eSTATE_APPROACH);
            // tolerance -> arrived
            else 
                setNextState(eSTATE_ARRIVED);
            break;
                        
        case eSTATE_APPROACH:
       
            // big dist -> drive
            if (absDist > dH)
                setNextState(eSTATE_DRIVE);
            // small dist -> approach
            else if (absDist > dL)
            {
                doApproach(dist);                
                bsendAction = true;
            }
            // tolerance -> arrived
            else 
                setNextState(eSTATE_ARRIVED);
            break;

        case eSTATE_ARRIVED:
       
            // big dist -> drive
            if (absDist > dH)
            {
                setNextState(eSTATE_DRIVE);
                LOG4CXX_INFO(logger, "target = " << targetPos);
                LOG4CXX_INFO(logger, "ist = " << istPos);
            }
            // small dist -> approach
            else if (absDist > dL)
            {
                setNextState(eSTATE_APPROACH);
            }
            // tolerance -> arrived (nothing)
            break;

        case eSTATE_FREE:
            
            // nothing to do
            break;            
    }   // end switch        
    
    if (bsendAction)
        writeBus();
}


// move joint to target position at drive speed
void AxisDriver::doDrive(float dist)
{    
    // deduce target speed (implies direction)
    int targetSpeed = (dist > 0.0) ? vDrive : -vDrive;    

    // compare target and real speeds
    int speedDif = targetSpeed - (int)istSpeed;    
    // if different, change joint speed (pushing it)
    if (fabs(speedDif) > vDriveTol)
    {
        if (speedDif > 0)
            outAction = JointMover::eMOV_PUSH_FRONT;
        else 
            outAction = JointMover::eMOV_PUSH_BACK;        
    }
    // if equal (under a tolerance), keep joint speed
    else
        outAction = JointMover::eMOV_KEEP;
}


// move joint to target position at approach speed
void AxisDriver::doApproach(float dist)
{
    // deduce target speed (implies direction)
    int targetSpeed = (dist > 0.0) ? vApproach : -vApproach;    

    // compare target and real speeds
    int speedDif = targetSpeed - (int)istSpeed;    
    // if different, change joint speed (pushing it)
    if (fabs(speedDif) > vApproachTol)
    {
        if (speedDif > 0)
            outAction = JointMover::eMOV_PUSH_FRONT;
        else 
            outAction = JointMover::eMOV_PUSH_BACK;        
    }
    // if equal (under a tolerance), keep joint speed
    else
        outAction = JointMover::eMOV_KEEP;    
}

void AxisDriver::showState()
{
    switch (getState())
    {
        case eSTATE_FREE:
            LOG4CXX_INFO(logger, ">> free");
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