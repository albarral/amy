#ifndef __AMY_ARM_FRONTALCYCLER_H
#define __AMY_ARM_FRONTALCYCLER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/bus/JointBus.h"
#include "amy/arm/util/ArmModule3.h"
#include "amy/control/Oscillator2.h"
#include "amy/math/EllipticMove.h"

namespace amy
{
// Module used to perform cyclic movements in the frontal plane (just involving pan & tilt).
// The module is able to combine two linear movements to perform elliptic trajectories.
// The module's inputs are: the frequency, two ortogonal amplitudes and the orientation angle.
// An oscillator is used to generate cyclic movements.
// The module outputs are: HS & VS accelerations.
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
    JointBus* pBusHS;      // bus connection to HS joint
    JointBus* pBusVS;      // bus connection to VS joint
    // control 
    Oscillator2 oOscillator2;     
    EllipticMove oEllipticMove;
    // output
    int priority;               // module's priority in control commands
    float xaccel;             // commanded axis speed 
    float yaccel;             // commanded axis speed 
    
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
        
        // apply accels for primary move
        void doPrimaryMove(int signal);
        // apply accels for secondary move
        void doSecondaryMove(int signal);
};
}
#endif
