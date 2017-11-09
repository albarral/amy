#ifndef __AMY_CORE_CYCLERBUS_H
#define __AMY_CORE_CYCLERBUS_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "tuly/control/brooks/controlT.h"

namespace amy
{
// Bus connections for a specific cycler
class CyclerBus
{
    private:        
        std::string cyclerName;
        
        // first cycler component
        tuly::ControlT<float> CO_CYCLER_FREQ1;              // movement frequency
        tuly::ControlT<float> CO_CYCLER_AMPLITUDE1;      // movement amplitude (degrees)
        tuly::ControlT<float> CO_CYCLER_ANGLE1;            // movement orientation (degrees)
        // second cycler component
        tuly::ControlT<float> CO_CYCLER_FREQ2;              // movement frequency
        tuly::ControlT<float> CO_CYCLER_AMPLITUDE2;      // movement amplitude (degrees)
        tuly::ControlT<float> CO_CYCLER_ANGLE2;            // movement orientation (degrees)
        // common to both components
        tuly::ControlT<bool> CO_CYCLER_ACTION;           // start/stop movement
                
    public:
        CyclerBus();
        //~CyclerBus();
        
        // initializes the class with the given cycler name
        void init (std::string cyclerName);        
        std::string& getCyclerName() {return cyclerName;};
                
        // first cycler component
        tuly::ControlT<float>& getCO_CYCLER_FREQ1() {return CO_CYCLER_FREQ1;};        
        tuly::ControlT<float>& getCO_CYCLER_AMPLITUDE1() {return CO_CYCLER_AMPLITUDE1;};        
        tuly::ControlT<float>& getCO_CYCLER_ANGLE1() {return CO_CYCLER_ANGLE1;};        
        // second cycler component
        tuly::ControlT<float>& getCO_CYCLER_FREQ2() {return CO_CYCLER_FREQ2;};        
        tuly::ControlT<float>& getCO_CYCLER_AMPLITUDE2() {return CO_CYCLER_AMPLITUDE2;};        
        tuly::ControlT<float>& getCO_CYCLER_ANGLE2() {return CO_CYCLER_ANGLE2;};        
        // common to both components
        tuly::ControlT<bool>& getCO_CYCLER_ACTION() {return CO_CYCLER_ACTION;};                
        
        std::string toString();
};

}    
#endif
