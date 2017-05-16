/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/bus/CyclerBus.h"

namespace amy
{
// Constructor
CyclerBus::CyclerBus ()
{    
    cyclerName = "cycler";
}

void CyclerBus::init(std::string cyclerName)
{
    this->cyclerName = cyclerName;
}

std::string CyclerBus::toString()
{
    std::string text = "CyclerBus:[" + cyclerName + "]\n" +       
         "CO_CYCLER_FREQ1: " + std::to_string(CO_CYCLER_FREQ1.getRequested()) + " - " + std::to_string(CO_CYCLER_FREQ1.getValue()) + "\n" +
         "CO_CYCLER_AMPLITUDE1: " + std::to_string(CO_CYCLER_AMPLITUDE1.getRequested()) + " - " + std::to_string(CO_CYCLER_AMPLITUDE1.getValue()) + "\n" +
         "CO_CYCLER_ANGLE1: " + std::to_string(CO_CYCLER_ANGLE1.getRequested()) + " - " + std::to_string(CO_CYCLER_ANGLE1.getValue()) + "\n" +
         "CO_CYCLER_FREQ2: " + std::to_string(CO_CYCLER_FREQ2.getRequested()) + " - " + std::to_string(CO_CYCLER_FREQ2.getValue()) + "\n" +
         "CO_CYCLER_AMPLITUDE2: " + std::to_string(CO_CYCLER_AMPLITUDE2.getRequested()) + " - " + std::to_string(CO_CYCLER_AMPLITUDE2.getValue()) + "\n" +
         "CO_CYCLER_ANGLE2: " + std::to_string(CO_CYCLER_ANGLE2.getRequested()) + " - " + std::to_string(CO_CYCLER_ANGLE2.getValue()) + "\n" +
         "CO_CYCLER_ACTION: " + std::to_string(CO_CYCLER_ACTION.getRequested()) + " - " + std::to_string(CO_CYCLER_ACTION.getValue()) + "\n" +
         "CO_CYCLER_PHASE: " + std::to_string(CO_CYCLER_PHASE.getRequested()) + " - " + std::to_string(CO_CYCLER_PHASE.getValue()) + "\n" +
            "\n";
    
    return text;
}

}
