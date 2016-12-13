/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/ArmDriver.h"
//#include "amy/show/Plot.h"  //  tmp for analysis

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmDriver::logger(Logger::getLogger("amy.arm"));

ArmDriver::ArmDriver()
{
    benabled = false;
    modName = "ArmDriver";
    
    bconnected = false;
    pBus = 0;
    pMovementControl = 0;
    pArm = 0;        
}

//ArmDriver2::~ArmDriver2()
//{
//}

void ArmDriver::init(Arm& oArm, MovementControl& oMovementControl)
{
    pMovementControl = &oMovementControl;      
    pArm = &oArm;
    // set specific preparation (in derived class)
    prepareDriver();
    benabled = true;

    LOG4CXX_INFO(logger, modName << " initialized");                  
    LOG4CXX_INFO(logger, oMovementControl.toString());      
};

void ArmDriver::connect(ArmBus* pArmBus)
{
    pBus = pArmBus;
    // set specific connections (in derived class)
    connectDriver();
    bconnected = true;
    
    LOG4CXX_DEBUG(logger, modName << " connected to bus");      
}

void ArmDriver::first()
{
    // start at done
    bnewMove = false;    
    bmoveDone = true;
    bmoveBlocked = false;
    setState(eSTATE_DONE);
    
    log4cxx::NDC::push(modName);   	
}
                    
void ArmDriver::moveRequested()
{
    bnewMove = true;  
}

void ArmDriver::moveDone()
{
    bmoveDone = true;    
}

void ArmDriver::moveBlocked()
{
    bmoveBlocked = true;
}


// performs a cyclic wave movement of the elbow
void ArmDriver::loop()
{
    senseBus();
    
    // if new move requested -> go to DRIVE
    if (bnewMove)
    {
        bnewMove = false;    
        bmoveBlocked = false;
        bmoveDone = false;      
        // set specific move preparation (in derived class)
        prepareMove();        

        // record output for analysis
        // oRecord.reset();
        setState(eSTATE_DRIVE);
    }

    // skip if DONE  
    if (getState() == eSTATE_DONE)
        return;
        
    if (isStateChanged())
        showState();
      
    // otherwise,drive joint
    if (getState() == eSTATE_DRIVE)
    {
        // perform specific movement (in derived class)
        doMove();
        
        // if movement blocked or finished -> DONE
        if (bmoveBlocked || bmoveDone)
        {       
            setState(eSTATE_DONE);   
            showState();
        }
    }
                    
    // record output for analysis
    //oRecord.addElement(istSpeed, sollAccel);
    
    // send commands
    writeBus();        
}

//void ArmDriver::done()
//{         
//    //Plot::plotRecord(oRecord, 60);
//}

void ArmDriver::showState()
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


}