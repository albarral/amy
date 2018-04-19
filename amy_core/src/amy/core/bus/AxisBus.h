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
#include "tron/control/operators/ControlAdder3.h"

namespace amy
{
// Bus connections for a specific axis (pan, tilt, radius)    
class AxisBus
{
    private:        
        std::string busName;
        
        // AxisRacer
        tron::Control3 CO_AXIS_SPEED1;          // axis primary speed (degrees/s)
        tron::Control3 CO_AXIS_SPEED2;        // axis secondary speed (degrees/s)
        tron::Control3 CO_AXIS_SPEED3;        // axis third speed (degrees/s)
        tron::ControlAdder3 CO_AXIS_SPEEDS;     // sum of axis speeds (degrees/s)
        // AxisDriver
        tron::Control2 CO_AXIS_POS;                // axis target position (degrees)
        
        // SENSORS
        // ArmSense
        tron::Sensor3 SO_AXIS_POS;             // axis real position (degrees)
        tron::Sensor3 SO_AXIS_SPEED;         // axis real speed (degrees/s)
                
    public:
        AxisBus();
        //~AxisBus();
        
        // set bus name
        void setBusName(std::string name) {busName = name;};                
        std::string& getBusName() {return busName;};
                
        // AxisRacer
        tron::Control3& getCO_AXIS_SPEED1() {return CO_AXIS_SPEED1;};        
        tron::Control3& getCO_AXIS_SPEED2() {return CO_AXIS_SPEED2;};        
        tron::Control3& getCO_AXIS_SPEED3() {return CO_AXIS_SPEED3;};        
        tron::ControlAdder3& getCO_AXIS_SPEEDS() {return CO_AXIS_SPEEDS;};        
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
