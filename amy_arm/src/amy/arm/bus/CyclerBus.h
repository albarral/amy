#ifndef __AMY_ARM_CYCLERBUS_H
#define __AMY_ARM_CYCLERBUS_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/control/brooks/controlT.h"

namespace amy
{
// Bus connections for a specific cycler
class CyclerBus
{
    private:        
        std::string cyclerName;
        
        // first cycler component
        ControlT<float> CO_CYCLER_FREQ1;              // movement frequency
        ControlT<float> CO_CYCLER_AMPLITUDE1;      // movement amplitude (degrees)
        ControlT<float> CO_CYCLER_ANGLE1;            // movement orientation (degrees)
        // second cycler component
        ControlT<float> CO_CYCLER_FREQ2;              // movement frequency
        ControlT<float> CO_CYCLER_AMPLITUDE2;      // movement amplitude (degrees)
        ControlT<float> CO_CYCLER_ANGLE2;            // movement orientation (degrees)
        // common to both components
        ControlT<bool> CO_CYCLER_ACTION;           // start/stop movement
        ControlT<int> CO_CYCLER_PHASE;                 // phase between components 
                
    public:
        CyclerBus();
        //~CyclerBus();
        
        // initializes the class with the given cycler name
        void init (std::string cyclerName);        
        std::string& getCyclerName() {return cyclerName;};
                
        // first cycler component
        ControlT<float>& getCO_CYCLER_FREQ1() {return CO_CYCLER_FREQ1;};        
        ControlT<float>& getCO_CYCLER_AMPLITUDE1() {return CO_CYCLER_AMPLITUDE1;};        
        ControlT<float>& getCO_CYCLER_ANGLE1() {return CO_CYCLER_ANGLE1;};        
        // second cycler component
        ControlT<float>& getCO_CYCLER_FREQ2() {return CO_CYCLER_FREQ2;};        
        ControlT<float>& getCO_CYCLER_AMPLITUDE2() {return CO_CYCLER_AMPLITUDE2;};        
        ControlT<float>& getCO_CYCLER_ANGLE2() {return CO_CYCLER_ANGLE2;};        
        // common to both components
        ControlT<bool>& getCO_CYCLER_ACTION() {return CO_CYCLER_ACTION;};                
        ControlT<int>& getCO_CYCLER_PHASE() {return CO_CYCLER_PHASE;};        
        
        std::string toString();
};

}    
#endif
