#ifndef __AMY_ARM_MOVER_H
#define __AMY_ARM_MOVER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/utils/module2.h"
#include "amy/utils/Click.h"
#include "amy/arm/bus/ArmBus.h"

namespace amy
{
// Module that performs a cyclic horizontal arm movement
// It derives from base class Module2
// It has 5 states:
// WAIT
// RIGHT
// CHANGE
// LEFT
// STOP
class ArmMover : public Module2
{
public:
    // states of ArmMover module
    enum eType
    {
         eSTATE_WAIT,
         eSTATE_RIGHT, 
         eSTATE_CHANGE, 
         eSTATE_LEFT,
         eSTATE_STOP
    };

private:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    // params
    std::string modName;   // module name
    int timeChange;     // milliseconds
    std::string jointName;  // target joint
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pBus;
    // logic
    float realSpeed;
    int prevState;
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
       
       void start();
       void stop();
        
private:       
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        
        // read bus data
        void senseBus();
        // write action commands to bus
        void writeBus(int command);

        // shows the present state name
        void showState();
};
}
#endif
