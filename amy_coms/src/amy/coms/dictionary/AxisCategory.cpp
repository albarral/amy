/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/dictionary/AxisCategory.h"
#include "amy/coms/dictionary/ComsCommand.h"

namespace amy
{
AxisCategory::AxisCategory() : ComsCategory(ComsCategory::eCATEGORY_AXIS, "axis category")   
{
    // builds list of commands
    build();
}

void AxisCategory::build()
{
    listCommands.clear();
    
    // define axis position commands
    ComsCommand oCommand(ID, AxisCategory::eAXIS_PAN_POS, "pan", 1, "move pan (degrees)");    
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, AxisCategory::eAXIS_TILT_POS, "tilt", 1, "move tilt (degrees)");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, AxisCategory::eAXIS_RAD_POS, "rad", 1, "move radius (cm)");
    listCommands.push_back(oCommand);
    // define axis speed commands
    oCommand = ComsCommand(ID, AxisCategory::eAXIS_PAN_SPEED, "vpan", 1, "move pan at given speed (degrees/s)");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, AxisCategory::eAXIS_TILT_SPEED, "vtilt", 1, "move tilt at given speed (degrees/s)");
    listCommands.push_back(oCommand);
    oCommand = ComsCommand(ID, AxisCategory::eAXIS_RAD_SPEED, "vrad", 1, "move tilt at given speed (degrees/s)");
    listCommands.push_back(oCommand);
}
    
bool AxisCategory::isValidAction(int value)
{
    return (value > AxisCategory::eAXIS_UNDEF && value < AxisCategory::eAXIS_DIM);
}

}