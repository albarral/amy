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
// Module to perform predefined cyclic movements with the arm.
// It controls two cycler modules simultaneously to achieve complex moves.
// States: 
// The module is normally in WAIT state. It jumps to TALK state to send commands and returns back to WAIT.
// Messages:
// The module sends 3 types of messages using different bus channels.     
class ArmMover : public ArmModule3
{
public:
    // states of ArmMover module
    enum eType
    {
         eSTATE_WAIT,           // just senses bus
         eSTATE_TALK           // sends commands to cyclers
    };
private:    
    // types of message
    enum eMsg
    {
         eMSG_TRIGGER,       // starts a cyclic movement   
         eMSG_STOP,           // ends a cyclic movement   
         eMSG_UPDATE       // modifies a cyclic movement
    };

    static log4cxx::LoggerPtr logger;
    // bus
    CyclerBus* pBusFrontalCycler;  // bus connection for this cycler
    // logic
    MoveFactory oMoveFactory;    
    CyclicMove oCyclicMove;    
    int message;        // type of message to be sent

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
        
        // sends message to cyclers
        void talk2Cyclers();
        // triggers a cyclic movement
        void triggerMove();
        // stop a cyclic movement
        void stopMove();
        // changes a cyclic movement        
        void updateMove();
};
}
#endif
