#ifndef __AMY_CORE_CYCLERBUS_H
#define __AMY_CORE_CYCLERBUS_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "tron/control/brooks/control1.h"
#include "tron/control/brooks/control2.h"
#include "tron/control/brooks/control3.h"

namespace amy
{
// Bus connections for a specific cycler
class CyclerBus
{
    private:        
        std::string cyclerName;
        
        // first cycler component
        tron::Control3 CO_CYCLER_FREQ1;              // movement frequency
        tron::Control3 CO_CYCLER_AMP1;                // movement amplitude (degrees)
        tron::Control3 CO_CYCLER_ANGLE1;            // movement orientation (degrees)
        tron::Control2 CO_CYCLER_PHASE1;                 // movement phase(degrees)
        // second cycler component
        tron::Control3 CO_CYCLER_FREQ2;              // movement frequency
        tron::Control3 CO_CYCLER_AMP2;               // movement amplitude (degrees)
        tron::Control3 CO_CYCLER_ANGLE2;            // movement orientation (degrees)
        tron::Control2 CO_CYCLER_PHASE2;                 // movement phase(degrees)
        // common to both components
        tron::Control1 CO_CYCLER_ACTION;           // start/stop movement
                
    public:
        CyclerBus();
        //~CyclerBus();
        
        // initializes the class with the given cycler name
        void init (std::string cyclerName);        
        std::string& getCyclerName() {return cyclerName;};
                
        // first cycler component
        tron::Control3& getCO_CYCLER_FREQ1() {return CO_CYCLER_FREQ1;};        
        tron::Control3& getCO_CYCLER_AMP1() {return CO_CYCLER_AMP1;};        
        tron::Control3& getCO_CYCLER_ANGLE1() {return CO_CYCLER_ANGLE1;};        
        tron::Control2& getCO_CYCLER_PHASE1() {return CO_CYCLER_PHASE1;};           
        // second cycler component
        tron::Control3& getCO_CYCLER_FREQ2() {return CO_CYCLER_FREQ2;};        
        tron::Control3& getCO_CYCLER_AMP2() {return CO_CYCLER_AMP2;};        
        tron::Control3& getCO_CYCLER_ANGLE2() {return CO_CYCLER_ANGLE2;};        
        tron::Control2& getCO_CYCLER_PHASE2() {return CO_CYCLER_PHASE2;};           
        // common to both components
        tron::Control1& getCO_CYCLER_ACTION() {return CO_CYCLER_ACTION;};                
        
        std::string toString();
};

}    
#endif
