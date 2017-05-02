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
         "CO_CYCLER_FREQ: " + std::to_string(CO_CYCLER_FREQ.getRequested()) + " - " + std::to_string(CO_CYCLER_FREQ.getValue()) + "\n" +
         "CO_CYCLER_AMPLITUDE: " + std::to_string(CO_CYCLER_AMPLITUDE.getRequested()) + " - " + std::to_string(CO_CYCLER_AMPLITUDE.getValue()) + "\n" +
         "CO_CYCLER_ANGLE: " + std::to_string(CO_CYCLER_ANGLE.getRequested()) + " - " + std::to_string(CO_CYCLER_ANGLE.getValue()) + "\n" +
         "CO_CYCLER_ACTION: " + std::to_string(CO_CYCLER_ACTION.getRequested()) + " - " + std::to_string(CO_CYCLER_ACTION.getValue()) + "\n" +
            "\n";
    
    return text;
}

}
