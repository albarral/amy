/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/bus/ArmBeat.h"

namespace amy
{
// Constructor
//ArmBeat::ArmBeat ()
//{    
//}

std::string ArmBeat::toString()
{
    std::string text = "ArmBeat:[\n ArmPanner - " + oArmPannerBeat.toString() +   
          "ArmExtender - " + oArmExtenderBeat.toString() +   
          "HS - " + oHSBeat.toString() +   
          "VS - " + oVSBeat.toString() +   
          "EL - " + oELBeat.toString() +   
          "HW - " + oHWBeat.toString() +   
          "VW - " + oVWBeat.toString() +   
            "]\n";
    
    return text;
}

}
