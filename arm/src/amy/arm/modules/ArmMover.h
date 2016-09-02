#ifndef __AMY_ARM_MOVER_H
#define __AMY_ARM_MOVER_H

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
// Module to perform predefined arm movements 
// States:
// WAIT
// MOVE
// STOP
class ArmMover : public Module2
{
public:
    // states of ArmMover module
    enum eType
    {
         eSTATE_WAIT,
         eSTATE_MOVE,
         eSTATE_STOP
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
        ArmMover();
        //~ArmMover();
                
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
        
        // temp (movements should be stored in DB)
        void buildMovPajarita();
        
        // shows the present state name
        void showState();
};
}
#endif
