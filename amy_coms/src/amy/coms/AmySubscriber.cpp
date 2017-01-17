/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/AmySubscriber.h"

namespace amy
{

AmySubscriber::AmySubscriber()
{    
    benabled = false;
}

ArmData AmySubscriber::readArmControl()
{    
    ArmData oArmData;
    
    if (benabled)
    {
        // read the soll message
        std::string sollMessage = readInfo();
        // and transform it into proper control data
        oArmData.processSollMessage(sollMessage);
    }
    
    return oArmData;
}

}