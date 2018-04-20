#ifndef __AMY_ARM_ARMCYCLER_H
#define __AMY_ARM_ARMCYCLER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/util/ArmModule3.h"
#include "amy/core/bus/AxisBus.h"
#include "amy/core/bus/CyclerBus.h"
#include "tron/signals/DualOscillator.h"
#include "tron/math/CyclicComponent.h"

namespace amy
{
// Module used to perform cyclic movements in the frontal plane (just involving pan & tilt).
// Movement parameters (frequency, amplitude, orientation and phase) can be changed dynamically without restarting the movement.
// Movements are achieved by the use of a dual oscillator (a combination of two vectorial oscillators working synchronously).
// The module's outputs are the pan & tilt speeds.
class ArmCycler: public ArmModule3
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
    CyclerBus* pCyclerBus;  // bus connection for this cycler
    AxisBus* pPanBus;    // bus connection to pan axis
    AxisBus* pTiltBus;     // bus connection to tilt axis
    // control 
    tron::DualOscillator oDualOscillator;   
    tron::CyclicComponent oCyclicComponent1;    //  first cyclic component
    tron::CyclicComponent oCyclicComponent2;     // second cyclic component  
    // output
    int priority;               // module's priority in control commands
    float xspeed;             // commanded pan speed 
    float yspeed;             // commanded tilt speed 
    
public:
        ArmCycler();
        //~ArmCycler();                

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
