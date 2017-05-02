#ifndef __AMY_ARM_ARMMOVER_H
#define __AMY_ARM_ARMMOVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/util/ArmModule3.h"
#include "amy/arm/bus/CyclerBus.h"
#include "amy/math/MoveFactory.h"
#include "amy/math/CyclicMove.h"

namespace amy
{
// Module to perform predefined cyclic movements with the arm
// States:
// WAIT
// TALK
class ArmMover : public ArmModule3
{
public:
    // states of ArmMover module
    enum eType
    {
         eSTATE_WAIT,
         eSTATE_TALK
    };

private:
    static log4cxx::LoggerPtr logger;
    // bus
    CyclerBus* pBusFrontalCycler;  // bus connection for this cycler
    // logic
    MoveFactory oMoveFactory;    
    CyclicMove oCyclicMove;    
    bool barmed;    // the movement is armed (prepared)
    bool bcyclerAction;     // start/stop cycler movement
    float factor; // change factor

public:
        ArmMover();
        //~ArmMover();
                               
private:       
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        // read bus data
        virtual void senseBus();
        // write info (control & sensory) to bus
        virtual void writeBus();
        // show module initialization in logs
        virtual void showInitialized();
        // shows the present state name
        void showState();
};
}
#endif
