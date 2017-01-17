/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/AmyPublisher.h"

namespace amy
{

AmyPublisher::AmyPublisher()
{    
    bconnected = false;
    pArmInterface = 0;
}

void AmyPublisher::connect2Arm(iArmInterface& oArmInterface)
{
    pArmInterface = &oArmInterface;
    bconnected = true;
}

void AmyPublisher::publishArmControl()
{    
    if (bconnected)
    {
        oArmData.setSoll1(pArmInterface->getHSControl());
        oArmData.setSoll2(pArmInterface->getVSControl());
        oArmData.setSoll3(pArmInterface->getELControl());
        oArmData.setSoll4(pArmInterface->getHWControl());
        oArmData.setSoll5(pArmInterface->getVWControl());
        
        publishInfo();
    }
}

}