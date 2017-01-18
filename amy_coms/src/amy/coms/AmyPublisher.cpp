/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/AmyPublisher.h"

namespace amy
{

AmyPublisher::AmyPublisher()
{    
    benabled = false;
}


void AmyPublisher::publishArmControl(ArmData& oArmData)
{    
    if (benabled)
    {
        // obtain the soll message
        std::string sollMessage = oArmData.createSollMessage();
        // and broadcast it
        publishInfo(sollMessage);
    }
}

}