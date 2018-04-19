/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/core/bus/AxisBus.h"

namespace amy
{
// Constructor
AxisBus::AxisBus ()
{    
    busName = "axis";
    
    // connect axis speeds to adder
    CO_AXIS_SPEEDS.connect(1, CO_AXIS_SPEED1);
    CO_AXIS_SPEEDS.connect(2, CO_AXIS_SPEED2);
    CO_AXIS_SPEEDS.connect(3, CO_AXIS_SPEED3);
}

std::string AxisBus::toString()
{
    std::string text = "AxisBus:[" + busName + "]\n" +       
         "CO_AXIS_SPEED1: " + std::to_string(CO_AXIS_SPEED1.getRequested()) + " - " + std::to_string(CO_AXIS_SPEED1.getValue()) + "\n" +
         "CO_AXIS_SPEED2: " + std::to_string(CO_AXIS_SPEED2.getRequested()) + " - " + std::to_string(CO_AXIS_SPEED2.getValue()) + "\n" +
         "CO_AXIS_SPEED3: " + std::to_string(CO_AXIS_SPEED3.getRequested()) + " - " + std::to_string(CO_AXIS_SPEED3.getValue()) + "\n" +
         "CO_AXIS_POS: " + std::to_string(CO_AXIS_POS.getRequested()) + " - " + std::to_string(CO_AXIS_POS.getValue()) + "\n" +
         "SO_AXIS_POS: " + std::to_string(SO_AXIS_POS.getValue()) + "\n" +
         "SO_AXIS_SPEED: " + std::to_string(SO_AXIS_SPEED.getValue()) + "\n" +
            "\n";
    
    return text;
}

}
