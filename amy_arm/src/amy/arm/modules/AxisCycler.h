#ifndef __AMY_ARM_AXISCYCLER_H
#define __AMY_ARM_AXISCYCLER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/arm/bus/AxisBus.h"
#include "amy/arm/util/ArmModule3.h"
#include "amy/control/Oscillator.h"

namespace amy
{
// Module used to perform cyclic movements with an axis.  
// The movement is specified by a frequency and an amplitude
// An oscillator is used to generate the cyclic output, which is the axis speed..
// The speed is tuned continously to achieve the requested amplitude.
class AxisCycler: public ArmModule3
{
public:
    // states 
    enum eState
    {
         eSTATE_DONE,        // nothing done
         eSTATE_START,       // trigger requested
         eSTATE_GO,            // cyclic movement
         eSTATE_STOP         // stop requested
    };
   
protected:
    static log4cxx::LoggerPtr logger;
    // bus
    AxisBus* pAxisBus;      // bus connection to controlled axis
    // input
    float frequency;             // oscillator frequency (Hz)
    float amplitude;             // amplitude of cyclic movement (degrees)    
    // control 
    Oscillator oOscillator;      
    float tunedSpeed;          // tuned speed of the movement (deg/s)
    float signal;
    float lastSignal;
    // output
    int priority;                    // module's priority in control commands
    float outSpeed;             // commanded axis speed 
    
public:
        AxisCycler();
        //~AxisCycler();                

protected:
        // connect module to specific axis
        virtual void tune2Axis() = 0;        
        
private:
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        // read bus data
        virtual void senseBus();
        // write info (control & sensory) to bus
        virtual void writeBus();
        // updates the movement speed
        void tuneSpeed();  
        // show module initialization in logs
        virtual void showInitialized();
        // shows the present state name
        void showState();
};
}
#endif
