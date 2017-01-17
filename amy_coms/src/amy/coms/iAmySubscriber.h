#ifndef __AMY_COMS_IAMYSUBSCRIBER_H
#define __AMY_COMS_IAMYSUBSCRIBER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/data/ArmData.h"

namespace amy
{
// Interface for amy subscriber classes (used for publish-subscribe communications)
class iAmySubscriber
{    
public:
    // read published joint control positions (angles)
    virtual ArmData readArmControl() = 0;
};
}
#endif