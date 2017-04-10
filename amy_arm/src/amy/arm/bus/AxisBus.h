#ifndef __AMY_ARM_AXISBUS_H
#define __AMY_ARM_AXISBUS_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/control/brooks/control.h"
#include "amy/control/brooks/controlT.h"
#include "amy/control/brooks/sensorT.h"

namespace amy
{
// Bus connections for a specific axis (pan, tilt, radius)    
class AxisBus
{
    private:        
        std::string axisName;
        
        // AxisRacer
        ControlT<float> CO_AXIS_SPEED;          // axis speed (degrees/s)
        ControlT<float> CO_AXIS_SPEED2;        // axis secondary speed (degrees/s)
        // AxisDriver
        ControlT<int> CO_AXIS_POS;                // axis target position (degrees)
        
        // SENSORS
        // ArmSense
        SensorT<float> SO_AXIS_POS;             // axis real position (degrees)
        SensorT<float> SO_AXIS_SPEED;         // axis real speed (degrees/s)
                
    public:
        AxisBus();
        //~AxisBus();
        
        // initializes the class with the given axis name
        void init (std::string axisName);        
        std::string& getAxisName() {return axisName;};
                
        // AxisRacer
        ControlT<float>& getCO_AXIS_SPEED() {return CO_AXIS_SPEED;};        
        ControlT<float>& getCO_AXIS_SPEED2() {return CO_AXIS_SPEED2;};        
        // AxisDriver
        ControlT<int>& getCO_AXIS_POS() {return CO_AXIS_POS;};        
        
        // SENSORS
        // ArmSense
        SensorT<float>& getSO_AXIS_POS() {return SO_AXIS_POS;};        
        SensorT<float>& getSO_AXIS_SPEED() {return SO_AXIS_SPEED;};        
        
        std::string toString();
};

}    
#endif
