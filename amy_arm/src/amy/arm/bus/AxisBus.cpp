/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/bus/AxisBus.h"

namespace amy
{
// Constructor
AxisBus::AxisBus ()
{    
    axisName = "axis";
}

void AxisBus::init(std::string axisName)
{
    this->axisName = axisName;
}

std::string AxisBus::toString()
{
    std::string text = "AxisBus:[" + axisName + "]\n" +       
         "CO_AXIS_FREQUENCY: " + std::to_string(CO_AXIS_FREQUENCY.getRequested()) + " - " + std::to_string(CO_AXIS_FREQUENCY.getValue()) + "\n" +
         "CO_AXIS_AMPLITUDE: " + std::to_string(CO_AXIS_AMPLITUDE.getRequested()) + " - " + std::to_string(CO_AXIS_AMPLITUDE.getValue()) + "\n" +
         "CO_AXIS_TRIGGER: " + std::to_string(CO_AXIS_TRIGGER.getRequested()) + "\n" +
         "CO_AXIS_STOP: " + std::to_string(CO_AXIS_STOP.getRequested()) + "\n" +
         "CO_AXIS_SPEED: " + std::to_string(CO_AXIS_SPEED.getRequested()) + " - " + std::to_string(CO_AXIS_SPEED.getValue()) + "\n" +
         "CO_AXIS_POS: " + std::to_string(CO_AXIS_POS.getRequested()) + " - " + std::to_string(CO_AXIS_POS.getValue()) + "\n" +
         "SO_AXIS_POS: " + std::to_string(SO_AXIS_POS.getValue()) + "\n" +
         "SO_AXIS_SPEED: " + std::to_string(SO_AXIS_SPEED.getValue()) + "\n" +
            "\n";
    
    return text;
}

}
