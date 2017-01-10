/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/util/ArmModule.h"

namespace amy
{
// Constructor 
ArmModule::ArmModule()
{    
    modName = "ArmModule";
    level = -1;
    benabled = false;
    bconnected = false;
    pArmBus = 0;
 }

void ArmModule::connect(ArmBus& oArmBus)
{
    pArmBus = &oArmBus;    
    bconnected = true;
}

}