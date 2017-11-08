#ifndef __AMY_COMS_AMYCOMS_H
#define __AMY_COMS_AMYCOMS_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "amy/coms/modules/AmyBroadcaster.h"
#include "amy/coms/modules/AmyListener.h"
#include "amy/core/bus/ArmBus.h"
#include "amy/core/config/AmyConfig.h"

namespace amy
{
class AmyComs
{
private:    
    static log4cxx::LoggerPtr logger;      
    AmyConfig oAmyConfig;
    AmyListener oAmyListener;               // communications module for responding to external requests
    AmyBroadcaster oAmyBroadcaster;   // communications module for broadcasting the control info

public:
  AmyComs();
  ~AmyComs();

   // launches the coms modules
   bool launch(ArmBus& oArmBus);
   // ends the coms modules
   bool end();
   
    // checks if amy end has been requested
    bool checkAmyEndRequested();      
};
}		

#endif
