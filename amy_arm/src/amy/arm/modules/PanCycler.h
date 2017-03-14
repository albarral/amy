#ifndef __AMY_ARM_PANCYCLER_H
#define __AMY_ARM_PANCYCLER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/control/Oscillator.h"
#include "amy/arm/util/ArmModule3.h"

namespace amy
{
// Module to perform cyclic movements with the pan axis.     
class PanCycler: public ArmModule3
{
public:
    // states of ArmRacer module
    enum eState
    {
         eSTATE_DONE,        // nothing done
         eSTATE_START,      // action requested
         eSTATE_GO            // cyclic movement
    };
   
protected:
    static log4cxx::LoggerPtr logger;
    // control 
    Oscillator oOscillator;      
    float amplitude;             // amplitude of cyclic movement (degrees)    
    float period;                    // period of the cyclic movement (s)
    float cruiseSpeed;         // value of applied cruise speed (deg/s)
    float signal;
    float lastSignal;
    // output
    int priority;                    // module's priority in control commands
    float panSpeed;             // pan speed applied
    
public:
        PanCycler();
        //~ArmRacer();                

protected:
        // read bus data
        virtual void senseBus();
        // write info (control & sensory) to bus
        virtual void writeBus();
        
private:
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        // updates the cruise speed 
        void updateCruiseSpeed();  
        // show module initialization in logs
        virtual void showInitialized();
        // shows the present state name
        void showState();
};
}
#endif
