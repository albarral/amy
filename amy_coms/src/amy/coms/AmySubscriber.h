#ifndef __AMY_COMS_AMYSUBSCRIBER_H
#define __AMY_COMS_AMYSUBSCRIBER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/coms/iAmySubscriber.h"
#include "amy/coms/data/ArmData.h"

namespace amy
{
// Base class used to subscribe to amy generated info (to be used by external processes).
class AmySubscriber : public iAmySubscriber
{    
protected:
    bool benabled;        
        
public:
    AmySubscriber();

   virtual void init() = 0;
   bool isEnabled() {return benabled;};
   
    // read published joint control positions (angles)
    virtual ArmData readArmControl();
    
private:
   // info reading method (specific for each AmySubscriber implementation)
    virtual std::string readInfo() = 0;
};
}
#endif
