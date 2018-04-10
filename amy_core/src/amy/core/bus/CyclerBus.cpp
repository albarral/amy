/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/core/bus/CyclerBus.h"

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
         "CO_CYCLER_AMP1: " + std::to_string(CO_CYCLER_AMP1.getRequested()) + " - " + std::to_string(CO_CYCLER_AMP1.getValue()) + "\n" +
         "CO_CYCLER_ANGLE1: " + std::to_string(CO_CYCLER_ANGLE1.getRequested()) + " - " + std::to_string(CO_CYCLER_ANGLE1.getValue()) + "\n" +
         "CO_CYCLER_PHASE1: " + std::to_string(CO_CYCLER_PHASE1.getRequested()) + " - " + std::to_string(CO_CYCLER_PHASE1.getValue()) + "\n" +
         "CO_CYCLER_FREQ2: " + std::to_string(CO_CYCLER_FREQ2.getRequested()) + " - " + std::to_string(CO_CYCLER_FREQ2.getValue()) + "\n" +
         "CO_CYCLER_AMP2: " + std::to_string(CO_CYCLER_AMP2.getRequested()) + " - " + std::to_string(CO_CYCLER_AMP2.getValue()) + "\n" +
         "CO_CYCLER_ANGLE2: " + std::to_string(CO_CYCLER_ANGLE2.getRequested()) + " - " + std::to_string(CO_CYCLER_ANGLE2.getValue()) + "\n" +
         "CO_CYCLER_PHASE2: " + std::to_string(CO_CYCLER_PHASE2.getRequested()) + " - " + std::to_string(CO_CYCLER_PHASE2.getValue()) + "\n" +
         "CO_CYCLER_ACTION: " + std::to_string(CO_CYCLER_ACTION.getRequested()) + " - " + std::to_string(CO_CYCLER_ACTION.getValue()) + "\n" +
            "\n";
    
    return text;
}

}
