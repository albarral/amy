#ifndef __AMY_CORE_AXISBUS_H
#define __AMY_CORE_AXISBUS_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "tron/control/brooks/control.h"
#include "tron/control/brooks/controlT.h"
#include "tron/control/brooks/sensorT.h"

namespace amy
{
// Bus connections for a specific axis (pan, tilt, radius)    
class AxisBus
{
    private:        
        std::string axisName;
        
        // AxisRacer
        tron::ControlT<float> CO_AXIS_SPEED;          // axis speed (degrees/s)
        tron::ControlT<float> CO_AXIS_SPEED2;        // axis secondary speed (degrees/s)
        // AxisDriver
        tron::ControlT<int> CO_AXIS_POS;                // axis target position (degrees)
        
        // SENSORS
        // ArmSense
        tron::SensorT<float> SO_AXIS_POS;             // axis real position (degrees)
        tron::SensorT<float> SO_AXIS_SPEED;         // axis real speed (degrees/s)
                
    public:
        AxisBus();
        //~AxisBus();
        
        // initializes the class with the given axis name
        void init (std::string axisName);        
        std::string& getAxisName() {return axisName;};
                
        // AxisRacer
        tron::ControlT<float>& getCO_AXIS_SPEED() {return CO_AXIS_SPEED;};        
        tron::ControlT<float>& getCO_AXIS_SPEED2() {return CO_AXIS_SPEED2;};        
        // AxisDriver
        tron::ControlT<int>& getCO_AXIS_POS() {return CO_AXIS_POS;};        
        
        // SENSORS
        // ArmSense
        tron::SensorT<float>& getSO_AXIS_POS() {return SO_AXIS_POS;};        
        tron::SensorT<float>& getSO_AXIS_SPEED() {return SO_AXIS_SPEED;};        
        
        std::string toString();
};

}    
#endif
