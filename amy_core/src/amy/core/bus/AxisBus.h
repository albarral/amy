#ifndef __AMY_CORE_AXISBUS_H
#define __AMY_CORE_AXISBUS_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "tron/control/brooks/control2.h"
#include "tron/control/brooks/control3.h"
#include "tron/control/brooks/sensor3.h"

namespace amy
{
// Bus connections for a specific axis (pan, tilt, radius)    
class AxisBus
{
    private:        
        std::string axisName;
        
        // AxisRacer
        tron::Control3 CO_AXIS_SPEED;          // axis speed (degrees/s)
        tron::Control3 CO_AXIS_SPEED2;        // axis secondary speed (degrees/s)
        // AxisDriver
        tron::Control2 CO_AXIS_POS;                // axis target position (degrees)
        
        // SENSORS
        // ArmSense
        tron::Sensor3 SO_AXIS_POS;             // axis real position (degrees)
        tron::Sensor3 SO_AXIS_SPEED;         // axis real speed (degrees/s)
                
    public:
        AxisBus();
        //~AxisBus();
        
        // initializes the class with the given axis name
        void init (std::string axisName);        
        std::string& getAxisName() {return axisName;};
                
        // AxisRacer
        tron::Control3& getCO_AXIS_SPEED() {return CO_AXIS_SPEED;};        
        tron::Control3& getCO_AXIS_SPEED2() {return CO_AXIS_SPEED2;};        
        // AxisDriver
        tron::Control2& getCO_AXIS_POS() {return CO_AXIS_POS;};        
        
        // SENSORS
        // ArmSense
        tron::Sensor3& getSO_AXIS_POS() {return SO_AXIS_POS;};        
        tron::Sensor3& getSO_AXIS_SPEED() {return SO_AXIS_SPEED;};        
        
        std::string toString();
};

}    
#endif
