#ifndef __AMY_ARM_FRONTALCYCLER_H
#define __AMY_ARM_FRONTALCYCLER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/util/ArmModule3.h"
#include "amy/arm/bus/AxisBus.h"
#include "amy/arm/bus/CyclerBus.h"
#include "amy/math/TriangularSignal.h"
#include "amy/math/Vector.h"

namespace amy
{
// Module used to perform cyclic linear movements in the frontal plane (just involving pan & tilt).
// The module's inputs are: the frequency, the movement amplitude and the orientation angle.
// A triangular signal is used to generate the cyclic movements.
// The module outputs are: pan & tilt speeds.
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
    float freq;             // movement frequency (Hz))
    float amplitude;     // movement amplitude (degrees)
    float movSpeed;     // max speed for the movement
    TriangularSignal oTriangularSignal;     
    Vector oSpeedVector;
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
