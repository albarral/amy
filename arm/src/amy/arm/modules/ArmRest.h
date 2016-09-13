#ifndef __AMY_ARM_REST_H
#define __AMY_ARM_REST_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/data/Movement.h"
#include "amy/arm/data/MoveStep.h"
#include "amy/utils/module2.h"
#include "amy/utils/Click.h"

namespace amy
{
// Behaviour that brings the arm to its rest position.
// It works: slowly, always, with tolerance (stops around rest position)
// params:
// d1: arrived distance (position tolerance)
// d2: approach distance (d2 > d1)    
// v1: approach speed
// v2: drive speed (v2 > v1)    
// States:
// DRIVE:           while dist > d2 -> FOR/BAC
// APPROACH     while dist > d1 -> BRAKE/KEEP
// ARRIVED         while dist < d1 -> STOP 
class ArmRest : public Module2
{
public:
    // states of ArmRest module
    enum eType
    {
         eSTATE_ARRIVED,
         eSTATE_APPROACH,
         eSTATE_DRIVE
    };

private:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    // params
    std::string modName;   // module name
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pBus;
    // logic
    Movement oMovement;    // present movement (set of steps) to be done
    MoveStep oMoveStep;    // present movement (set of steps) to be done    
    int numStep;
    amy::Click oClick;  

public:
        ArmRest();
        //~ArmRest();
                
       // module params
       void init (int timeChange);
       bool isEnabled() {return benabled;};

       // bus connection 
       void connect(ArmBus& oConnections);
       bool isConnected() {return bconnected;};
       
               
private:       
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        
        // read bus data
        void senseBus();
        // write action commands to bus
        void writeBus();
        
        void fetchMovement();
        void startMovement();
        void stopMovement();
        bool newStep();
        
        // shows the present state name
        void showState();
};
}
#endif
