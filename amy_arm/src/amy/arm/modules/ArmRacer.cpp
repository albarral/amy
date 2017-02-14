/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "amy/arm/modules/ArmRacer.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmRacer::logger(Logger::getLogger("amy.arm"));

ArmRacer::ArmRacer()
{
    modName = "ArmRacer";
    priority = 1;
    pHSBus = 0;
    pVSBus = 0;
    pELBus = 0;    
}

//ArmRacer::~ArmRacer()
//{
//}

void ArmRacer::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}

void ArmRacer::first()
{
    // start at idle
    setState(eSTATE_IDLE);
    
    // tune PID controllers
    //float* pPID = oArmConfig.getTiltKeeperPID();
    float Kp = 4.0; 
    float Ki = 0.0;
    float Kd = 2.0;
    oSpeedControlPan.init(Kp, Ki, Kd);
    oSpeedControlTilt.init(Kp, Ki, Kd);
    oSpeedControlRad.init(Kp, Ki, Kd);
    // connect to specific joints
    pHSBus = &pArmBus->getBusHS();
    pVSBus = &pArmBus->getBusVS();
    pELBus = &pArmBus->getBusEL();

    log4cxx::NDC::push(modName);   	
}
                    

// drives the axis towards the target position
void ArmRacer::loop()
{
    senseBus();

    int state = getState();
    // skip if IDLE or BLOCKED
    if (state == eSTATE_IDLE ||state == eSTATE_BLOCKED)            
        return;
            
    switch (state)
    {
        case eSTATE_GO:     

            //reset PID controllers
            oSpeedControlPan.restart();
            oSpeedControlTilt.restart();
            oSpeedControlRad.restart();
            setState(eSTATE_DRIVE);
            break;  

        case eSTATE_DRIVE:
            // drive arm

            // HS control -> pan movement 
            accelHS = oSpeedControlPan.move(panSpeed, limitHS);              
            // VS control -> tilt movement 
            accelVS = oSpeedControlTilt.move(tiltSpeed, limitVS);              
            // PID control of ELB -> radial movement 
            accelELB = oSpeedControlRad.move(radialSpeed, limitELB);              
            writeBus();
            LOG4CXX_INFO(logger, "pan -> speed = " << panSpeed << " - " << oSpeedControlPan.toString());
            LOG4CXX_INFO(logger, "tilt -> speed = " << tiltSpeed << " - " << oSpeedControlTilt.toString());
            LOG4CXX_INFO(logger, "radius -> speed = " << radialSpeed << " - " << oSpeedControlRad.toString());
            
            // if movement blocked -> BLOCKED
            if (checkBlocked())
                setState(eSTATE_BLOCKED);   
            break;
    }   // end switch    

    if (isStateChanged())
        showState();

    writeBus();        
}

void ArmRacer::senseBus()
{
   if (pArmBus->getCO_RACER_ACTION().checkRequested())
   {
       // activate
       if (pArmBus->getCO_RACER_ACTION().getValue())
         setState(eSTATE_GO);   
       // deactivate
       else
         setState(eSTATE_IDLE);                            

       showState();
   }
    // get requested pan speed
    if (pArmBus->getCO_PAN_SPEED().checkRequested())
        oSpeedControlPan.setTargetSpeed(pArmBus->getCO_PAN_SPEED().getValue());
   
    // get requested tilt speed
   if (pArmBus->getCO_TILT_SPEED().checkRequested())
        oSpeedControlTilt.setTargetSpeed(pArmBus->getCO_TILT_SPEED().getValue());  
   
   // get requested radial speed
   if (pArmBus->getCO_RADIAL_SPEED().checkRequested())
        oSpeedControlRad.setTargetSpeed(pArmBus->getCO_RADIAL_SPEED().getValue());  
 
    // sense axis speeds
    panSpeed= pArmBus->getSO_PAN_SPEED().getValue();
    tiltSpeed= pArmBus->getSO_TILT_SPEED().getValue();
    radialSpeed= pArmBus->getSO_RADIUS_SPEED().getValue();
    
    // sense reached joint limits
    limitHS = pHSBus->getSO_JCONTROL_LIMIT_REACHED().getValue();
    limitVS = pVSBus->getSO_JCONTROL_LIMIT_REACHED().getValue();
    limitELB = pELBus->getSO_JCONTROL_LIMIT_REACHED().getValue();
}

void ArmRacer::writeBus()
{  
    pHSBus->getCO_JCONTROL_ACCEL().request(accelHS, priority);
    pVSBus->getCO_JCONTROL_ACCEL().request(accelVS, priority);
    pELBus->getCO_JCONTROL_ACCEL().request(accelELB, priority);
}

bool ArmRacer::checkBlocked()
{
//    int panSign = (panSpeed2 > 0.0 ? 1: -1);
//    int tiltSign = (tiltSpeed2 > 0.0 ? 1: -1);
//    int radSign = (radialSpeed2 > 0.0 ? 1: -1);
//
//    // check if movement is blocked (pushing beyond the joints limits)        
//    bool blockedPan = (limitHS > 0 && panSign > 0) || (limitHS < 0 && panSign < 0);
//    bool blockedTilt = (limitVS > 0 && tiltSign > 0) || (limitVS < 0 && tiltSign < 0);
//    bool blockedRad = (limitELB > 0 && radSign > 0) || (limitELB < 0 && radSign < 0);
//    
//    return (blockedPan && blockedTilt && blockedRad);
    return false;
}


void ArmRacer::showState()
{
    switch (getState())
    {
        case eSTATE_IDLE:
            LOG4CXX_INFO(logger, ">> idle");
            break;
                        
        case eSTATE_GO:
            LOG4CXX_INFO(logger, ">> go");
            break;

        case eSTATE_DRIVE:
            LOG4CXX_INFO(logger, ">> drive");
            break;

        case eSTATE_BLOCKED:
            LOG4CXX_INFO(logger, ">> blocked");
            break;
    }   // end switch    
}


}