/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/util/ArmModule3.h"

namespace amy
{
// Constructor 
ArmModule3::ArmModule3()
{    
    modName = "AmModule3";
    benabled = false;
    bconnected = false;
    pArmBus = 0;
 }

void ArmModule3::init(Arm& oArm, AmyArmConfig& oAmyArmConfig)
{
    this->oArm = oArm;
    this->oAmyArmConfig = oAmyArmConfig;
    benabled = true;
}

void ArmModule3::connect(ArmBus& oArmBus)
{
    pArmBus = &oArmBus;    
    bconnected = true;
}

}