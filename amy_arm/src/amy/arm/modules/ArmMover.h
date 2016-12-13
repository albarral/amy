#ifndef __AMY_ARM_MOVER_H
#define __AMY_ARM_MOVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/core/bus/ArmBus.h"
#include "amy/arm/data/Movement.h"
#include "amy/arm/data/MoveStep.h"
#include "amy/arm/util/ArmModule.h"
#include "amy/utils/Click.h"

namespace amy
{
// Module to perform predefined arm movements 
// States:
// WAIT
// MOVE
// STOP
class ArmMover : public ArmModule
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
    // logic
    Movement oMovement;    // present movement (set of steps) to be done
    MoveStep oMoveStep;    // present movement (set of steps) to be done    
    int numStep;
    amy::Click oClick;  

public:
        ArmMover();
        //~ArmMover();
                
       // module params
       virtual void init(Arm& oArm);
               
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
