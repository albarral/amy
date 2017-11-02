#ifndef __AMY_CORE_AXISBUS_H
#define __AMY_CORE_AXISBUS_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "tuly/control/brooks/control.h"
#include "tuly/control/brooks/controlT.h"
#include "tuly/control/brooks/sensorT.h"

namespace amy
{
// Bus connections for a specific axis (pan, tilt, radius)    
class AxisBus
{
    private:        
        std::string axisName;
        
        // AxisRacer
        tuly::ControlT<float> CO_AXIS_SPEED;          // axis speed (degrees/s)
        tuly::ControlT<float> CO_AXIS_SPEED2;        // axis secondary speed (degrees/s)
        // AxisDriver
        tuly::ControlT<int> CO_AXIS_POS;                // axis target position (degrees)
        
        // SENSORS
        // ArmSense
        tuly::SensorT<float> SO_AXIS_POS;             // axis real position (degrees)
        tuly::SensorT<float> SO_AXIS_SPEED;         // axis real speed (degrees/s)
                
    public:
        AxisBus();
        //~AxisBus();
        
        // initializes the class with the given axis name
        void init (std::string axisName);        
        std::string& getAxisName() {return axisName;};
                
        // AxisRacer
        tuly::ControlT<float>& getCO_AXIS_SPEED() {return CO_AXIS_SPEED;};        
        tuly::ControlT<float>& getCO_AXIS_SPEED2() {return CO_AXIS_SPEED2;};        
        // AxisDriver
        tuly::ControlT<int>& getCO_AXIS_POS() {return CO_AXIS_POS;};        
        
        // SENSORS
        // ArmSense
        tuly::SensorT<float>& getSO_AXIS_POS() {return SO_AXIS_POS;};        
        tuly::SensorT<float>& getSO_AXIS_SPEED() {return SO_AXIS_SPEED;};        
        
        std::string toString();
};

}    
#endif
