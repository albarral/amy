/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include "log4cxx/ndc.h"

#include "amy/arm/modules/AxisDriver.h"

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
}

//AxisDriver::~AxisDriver()
//{
//}

void AxisDriver::init(int dH, int dL, int vH, int vL)
{
    // valid params
    if (dH > 0 && dL > 0 && vH > 0 && vL > 0 && dH >= dL)
    {
        this->dH = dH;
        this->dL = dL;
        this->vH = vH;
        this->vL = vL;
        benabled = true;
        
        LOG4CXX_INFO(logger, modName << " initialized");                  
        LOG4CXX_DEBUG(logger, "dH=" << dH << ", dL=" << dL << ", vH=" << vH << ", vL=" << vL);      
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
    
    float dist = targetValue - istValue;
    float absDist = fabs(dist);
    
    switch (getState())
    {
        case eSTATE_DRIVE:
            
            if (absDist > dH)
                doDriveControl(dist);
            else if (absDist > dL)
                setNextState(eSTATE_APPROACH);
            else 
                setNextState(eSTATE_ARRIVED);
            break;
                        
        case eSTATE_APPROACH:
       
            if (absDist > dH)
                setNextState(eSTATE_DRIVE);
            else if (absDist > dL)
                doApproachControl(dist);                
            else 
                setNextState(eSTATE_ARRIVED);
            break;

        case eSTATE_ARRIVED:
       
            if (absDist <= dL)
                doArrivedControl(dist);                
            else if (absDist > dH)
                setNextState(eSTATE_DRIVE);
            else if (absDist > dL)
                setNextState(eSTATE_APPROACH);
            break;

        case eSTATE_FREE:
            
            // nothing to do
            break;            
    }   // end switch        
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