/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/ArmConnector.h"

namespace amy
{
ArmConnector::ArmConnector()
{    
    pArmBus = 0;
    bconnected = false;
}

void ArmConnector::connect2Bus(ArmBus& oArmBus)
{
    pArmBus = &oArmBus;
    bconnected = true;
}

}