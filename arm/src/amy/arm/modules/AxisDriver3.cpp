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
    pMovementControl = 0;
    sollAccel = 0;
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
    selectBusJoints();
    
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
    
    // if new move requested -> go to MOVE
    if (bnewMove)
    {
        bnewMove = false;    
        newMove();
    }

    // skip if DONE  
    if (getState() == eSTATE_DONE)
        return;
        
    if (isStateChanged())
        showState();
      
    // otherwise, drive joint
    if (getState() == eSTATE_DRIVE)
    {            
        sollAccel = oJointDriver.drive(istPos);
        
        LOG4CXX_INFO(logger, oJointDriver.toString());

        // if movement blocked or finished -> DONE
        if (isMovementBlocked() || oJointDriver.isMovementDone())
        {
            sollAccel = 0.0;
            done();
        }
    }
                    
    // record output for analysis
    //oRecord.addElement(istSpeed, sollAccel);
    
    // send commands
    writeBus();        
}

// check if movement is blocked (if pushing beyond the joint's limit)
bool AxisDriver3::isMovementBlocked()
{
    
    return ((limitReached > 0 && oJointDriver.getMoveSign() > 0) || (limitReached < 0 && oJointDriver.getMoveSign() < 0));
}

void AxisDriver3::newMove()
{
    // update movement params
    if (pMovementControl != 0)
    {
        oJointDriver.init(pMovementControl->getKaccelDriver(),
                               pMovementControl->getKspeedDriver(),
                               pMovementControl->getDriverTolerance(),
                               pMovementControl->getDriverSpeed());        
    }
        
    // set new target
    oJointDriver.setTarget(targetPos);
    // and go to MOVE
    setState(eSTATE_DRIVE);

    // record output for analysis
    oRecord.reset();
    // show data
    showMovementData();                    
}


void AxisDriver3::done()
{         
    setState(eSTATE_DONE);   
    showState();
    //Plot::plotRecord(oRecord, 60);
}

void AxisDriver3::showState()
{
    switch (getState())
    {
        case eSTATE_DONE:
            LOG4CXX_INFO(logger, ">> done");
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
    LOG4CXX_INFO(logger, oJointDriver.paramsToString());      
}

}