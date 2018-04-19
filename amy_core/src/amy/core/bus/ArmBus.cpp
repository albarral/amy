/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/core/bus/ArmBus.h"
#include "amy/core/robot/Joint.h"

namespace amy
{
// Constructor
ArmBus::ArmBus ()
{    
    benabled = false;
    armName = "none";
}

void ArmBus::init(Arm& oArm)
{
    armName = oArm.getName();
    
    // init cycler buses
    oFrontalCyclerBus.init("frontalcycler");
    
    // init axis buses
    oBusPan.setBusName(Arm::pan);
    oBusTilt.setBusName(Arm::tilt);
    oBusRadial.setBusName(Arm::radial);

    // init joint buses
    oBusHS.setBusName(Joint::getName4Type(Joint::eJOINT_HS));
    oBusVS.setBusName(Joint::getName4Type(Joint::eJOINT_VS));
    oBusEL.setBusName(Joint::getName4Type(Joint::eJOINT_ELB));
    oBusHW.setBusName(Joint::getName4Type(Joint::eJOINT_HW));
    oBusVW.setBusName(Joint::getName4Type(Joint::eJOINT_VW));
    
    benabled = true;
}

std::string ArmBus::toString()
{
    std::string text = "ArmBus:[" + armName + "]\n" +       
        "\n" + oFrontalCyclerBus.toString() +   
        "CO_KEEP_TILT: " + std::to_string(CO_KEEP_TILT.getRequested()) + " - " + std::to_string(CO_KEEP_TILT.getValue()) + "\n" +
        "\n" + oBusPan.toString() +   
        "\n" + oBusTilt.toString() +   
        "\n" + oBusRadial.toString() +   
//          "\n" + oBusHS.toString() +   
//          "\n" + oBusVS.toString() +   
//          "\n" + oBusEL.toString() +   
//          "\n" + oBusHW.toString() +   
//          "\n" + oBusVW.toString() + 
            "\n";
    
    return text;
}

}
