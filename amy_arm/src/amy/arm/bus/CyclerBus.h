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
        
        // cycler module
        ControlT<float> CO_CYCLER_FREQ;              // movement frequency
        ControlT<float> CO_CYCLER_AMPLITUDE;      // movement amplitude (degrees)
        ControlT<float> CO_CYCLER_ANGLE;            // movement orientation (degrees)
        ControlT<bool> CO_CYCLER_ACTION;           // start/stop movement
                
    public:
        CyclerBus();
        //~CyclerBus();
        
        // initializes the class with the given cycler name
        void init (std::string cyclerName);        
        std::string& getCyclerName() {return cyclerName;};
                
        ControlT<float>& getCO_CYCLER_FREQ() {return CO_CYCLER_FREQ;};        
        ControlT<float>& getCO_CYCLER_AMPLITUDE() {return CO_CYCLER_AMPLITUDE;};        
        ControlT<float>& getCO_CYCLER_ANGLE() {return CO_CYCLER_ANGLE;};        
        ControlT<bool>& getCO_CYCLER_ACTION() {return CO_CYCLER_ACTION;};        
        
        std::string toString();
};

}    
#endif
