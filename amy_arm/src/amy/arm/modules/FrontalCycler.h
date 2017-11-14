#ifndef __AMY_ARM_FRONTALCYCLER_H
#define __AMY_ARM_FRONTALCYCLER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/util/ArmModule3.h"
#include "amy/core/bus/AxisBus.h"
#include "amy/core/bus/CyclerBus.h"
#include "maty/math/LinearCycler.h"

namespace amy
{
// Module used to perform cyclic movements in the frontal plane (just involving pan & tilt).
// Movement parameters such as frequency, amplitude and orientation angle can be changed dynamically (without restarting the movement).
// Movements are achieved by the combination of two perpendicular linear cyclers working in a coordinated way.
// The module's outputs are the pan & tilt speeds.
class FrontalCycler: public ArmModule3
{
public:
    // states 
    enum eState
    {
         eSTATE_DONE,        // nothing done
         eSTATE_START,       // movement started
         eSTATE_GO,           // moving
         eSTATE_STOP         // stop requested
    };
   
private:
    static log4cxx::LoggerPtr logger;
    // bus 
    CyclerBus* pBusFrontalCycler;  // bus connection for this cycler
    AxisBus* pPanBus;    // bus connection to pan axis
    AxisBus* pTiltBus;     // bus connection to tilt axis
    // control 
    maty::LinearCycler oLinearCycler1;    // first cyclic component
    maty::LinearCycler oLinearCycler2;    // second cyclic component
    int phase;               // phase difference between both components
    // output
    int priority;               // module's priority in control commands
    float xspeed;             // commanded pan speed 
    float yspeed;             // commanded tilt speed 
    
public:
        FrontalCycler();
        //~FrontalCycler();                

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
        
        // trigger the movement
        void triggerMove();
        // perform the movement
        void updateMove();
        // stop the movement
        void stopMove();
        // update max speed for the movement
        void recomputeSpeed();
};
}
#endif
