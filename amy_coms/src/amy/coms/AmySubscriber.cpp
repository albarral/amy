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

//void AmySubscriber::init()
//{
//    benabled = true;
//}

ArmData AmySubscriber::readArmControl()
{    
    if (benabled)
    {
        std::string message = readInfo();
        
        oArmData.processSollMessage(message);
    }
    
    return oArmData;
}

}