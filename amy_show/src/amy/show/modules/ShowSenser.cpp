/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/modules/ShowSenser.h"

namespace amy
{
log4cxx::LoggerPtr ShowSenser::logger(log4cxx::Logger::getLogger("amy.show"));

// Constructor 
ShowSenser::ShowSenser()
{    
    modName = "ShowSenser";     
    bconnected = false;
    pHSBus = 0;
    pVSBus = 0;
    pELBus = 0;
    pPanBus = 0;
    pTiltBus = 0;
    pRadialBus = 0;
    benabled = false;    
    pShowData = 0;
 }

ShowSenser::~ShowSenser()
{
}

void ShowSenser::connect(ArmBus& oArmBus)
{
    pHSBus = &oArmBus.getBusHS();    
    pVSBus = &oArmBus.getBusVS();    
    pELBus = &oArmBus.getBusEL();   
    pPanBus = &oArmBus.getPanBus();
    pTiltBus = &oArmBus.getTiltBus(); 
    pRadialBus = &oArmBus.getRadialBus();
    
    bconnected = true;
}

void ShowSenser::init(ShowData& oShowData)
{
    pShowData = &oShowData;    
}

void ShowSenser::first()
{
    // if publishers enabled
    if (bconnected && pShowData != 0)
    {
        benabled = true;
        LOG4CXX_INFO(logger, "ShowSenser initialized");                                
    }
    else
        LOG4CXX_ERROR(logger, "ShowSenser: failed initialization, not connected!");                            
}
                    
void ShowSenser::loop()
{
    // exit if not enabled
    if (!benabled)
    {
        LOG4CXX_ERROR(logger, "ShowSenser: not enabled, loop ignored");
        return;
    }
    
    // axis positions
    pShowData->pan = pPanBus->getSO_AXIS_POS().getValue();
    pShowData->tilt = pTiltBus->getSO_AXIS_POS().getValue();    
    pShowData->radius = pRadialBus->getSO_AXIS_POS().getValue();
    // joint positions
    pShowData->angleVS = pVSBus->getSO_IST_ANGLE().getValue();
    pShowData->angleELB = pELBus->getSO_IST_ANGLE().getValue();
    // joint limits
    pShowData->stateHS = pHSBus->getSO_DRIVER_STATE().getValue(); 
    pShowData->stateVS = pVSBus->getSO_DRIVER_STATE().getValue(); 
    pShowData->stateELB = pELBus->getSO_DRIVER_STATE().getValue();     
    // pan speeds 
    pShowData->panSOSpeed = pPanBus->getSO_AXIS_SPEED().getValue();
    pShowData->panCOSpeed = pPanBus->getCO_AXIS_SPEED1().getValue();
    // tilt speeds
    pShowData->tiltSOSpeed = pTiltBus->getSO_AXIS_SPEED().getValue();
    pShowData->tiltCOSpeed = pTiltBus->getCO_AXIS_SPEED1().getValue();
}
}