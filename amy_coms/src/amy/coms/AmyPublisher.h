#ifndef __AMY_COMS_AMYPUBLISHER_H
#define __AMY_COMS_AMYPUBLISHER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/coms/iAmyPublisher.h"
#include "amy/coms/data/ArmData.h"


namespace amy
{
// Base class used to publish amy info (to be consumed by external processes)
class AmyPublisher : public iAmyPublisher
{    
protected:
    bool benabled;        // connected to amy interface
        
public:
    AmyPublisher();

    virtual void init() = 0;
    bool isEnabled() {return benabled;};
   
    // publish commanded joint control positions (angles)
    virtual void publishArmControl(ArmData& oArmData);
    
private:
   // info publishing method (specific for each AmyPublisher implementation)
    virtual void publishInfo(std::string sollMessage) = 0;
};
}
#endif
