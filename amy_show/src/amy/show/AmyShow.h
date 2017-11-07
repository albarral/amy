#ifndef __AMY_SHOW_AMYSHOW_H
#define __AMY_SHOW_AMYSHOW_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "amy/show/ShowData.h"
#include "amy/show/modules/ShowPlotter.h"
#include "amy/show/modules/ShowSenser.h"
#include "amy/core/bus/ArmBus.h"

namespace amy
{
class AmyShow
{
private:    
    static log4cxx::LoggerPtr logger;      
    ShowData oShowData;     //  shared show data
    ShowSenser oShowSenser; // module for info reading
    ShowPlotter oShowPlotter;   // module for info showing

public:
  AmyShow();
  ~AmyShow();

   // launches the show modules
   bool launch(ArmBus& oArmBus);
   // ends the show modules
   bool end();
};
}		

#endif
